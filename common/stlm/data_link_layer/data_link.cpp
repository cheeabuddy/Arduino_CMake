
#include "data_link.h"

#ifdef __RISC__
void
DataLinkLayer::attach_port (UartVirtual * prt)
{
    port = prt;
}
#endif

bool
DataLinkLayer::ready_to_send (void)
{
    return !buffer_send.is_blocked;
}

bool
DataLinkLayer::ready_to_read (void)
{
    return buffer_receive.is_blocked;
}

bool
DataLinkLayer::data_in (char * data, uint8_t length)
{
    if ( length >= BUFFER_SIZE )
    {
        return false;
    }
    else if ( ready_to_send() )
    {
        // Channel free to send
        buffer_send.data[0] = (char) length;
        strncpy(buffer_send.data+1,data,length);
        buffer_send.is_blocked = true;
        return true;
    }
    else
    {
        return false;
    }
}

bool
DataLinkLayer::data_out (char * data, uint8_t length)
{
    //std::cout << "yo : " << buffer_receive.is_blocked << "\n";
    // TODO : fix up
    if ( ready_to_read() )
    {
        uint8_t length_buf;
        length_buf = (uint8_t) buffer_receive.data[0];
        strncpy(data,buffer_receive.data+1,length_buf);
        buffer_receive.is_blocked = false;
        return true;
    }
    else
    {
        // No data in buffer
        return false;
    }
}


bool
DataLinkLayer::frame_send(void)
{
    if (ready_to_send())
    {
        // No data to send
        return false;
    }

    crc_t crc_check = 0;
    uint8_t data_length;

    data_length = ((uint8_t) buffer_send.data[0]) + 1;

    // Frame start
    port->write(FRAME_START, 2); //strlen(FRAME_START));

    // Data send
    port->write(buffer_send.data, data_length);

    // CRC send
    // TODO : crc settings
    if (crc_on)
    {
        //std::cout << sizeof(crc_t) << '\n';
        crc_check = crcFast((unsigned char *)buffer_send.data,data_length);
        port->write((char *)&crc_check,sizeof(crc_t));
    }

    // Frame end
    port->write(FRAME_END, 2); //strlen(FRAME_END));

    // TODO : ack settings
    if (!ack_on)
    {
        buffer_send.is_blocked = false;
    }

    return true;
}

bool
DataLinkLayer::status_send (frame_state_t status_type, bool state)
{
    char c[2] = {(char)status_type,(char)state};
    crc_t crc_check = 0;

    port->write(STATUS_START, 2); //strlen(FRAME_START));
    port->write(c, 2);

//    // CRC send
//    // TODO : crc settings
//    if (crc_on)
//    {
//        //std::cout << sizeof(crc_t) << '\n';
//        crc_check = crcFast((unsigned char *)c,2);
//        port->write((char *)&crc_check,sizeof(crc_t));
//    }

    port->write(STATUS_END, 2); //strlen(FRAME_END));

    return false;
}

frame_state_t
DataLinkLayer::frame_start_received (char c)
{
    static char frame[2] = {'\n','\n'};
    frame[1] = c;
    if(!strncmp(frame,FRAME_START,2))
    {
        frame[0] = 0;
        frame[1] = 0;
        return DATA;
    }
    else if(!strncmp(frame,STATUS_START,2))
    {
        frame[0] = 0;
        frame[1] = 0;
        return STATUS;
    }
    else
    {
        frame[0] = frame[1];
        frame[1] = 0;
        return START;
    }
}

frame_state_t
DataLinkLayer::frame_data_received (char c)
{
    static uint8_t pos = 0;
    static uint8_t length = 0;
    if(!pos)
    {
        length = (uint8_t) c;
    }
    if(pos <= length-1)
    {
        buffer_receive.data[pos] = c;
        pos++;
        return DATA;
    }
    else
    {
        buffer_receive.data[pos] = c;
        pos = 0;
        length = 0;
        return CRC;
    }
}

frame_state_t
DataLinkLayer::frame_status_received (char c)
{
    static uint8_t pos = 0;
    static frame_state_t status_type;
    if(pos == 0) {
        pos++;
        status_type = (frame_state_t) c;
        return STATUS;
    }
    else
    {
        bool state;
        state = (bool) c;
        if (status_type == STATUS)
        {
            buffer_receive.other_side_blocked = state;
        }
        else if (status_type == ACK)
        {
            // TODO : acking condition
            buffer_send.ack_status = state;
        }
        pos = 0;
        status_type = START;
        return END;
    }
}

frame_state_t
DataLinkLayer::frame_crc_received (char c)
{
    static uint8_t pos = 0;
    char gg = (char) pos;
    static char frame[2];
    frame[pos] = c;
    //std::cout << pos << '\n';
    if(pos < (sizeof(crc_t)-1)) {
        pos++;
        return CRC;
    }
    else
    {
        crc_t crc_check;
        uint8_t data_length;

        data_length = ((uint8_t) buffer_receive.data[0]) + 1;
        pos = 0;

        crc_check = crcFast((unsigned char *)buffer_receive.data,data_length);
        if (!strncmp(frame,(char *) &crc_check,sizeof(crc_t)))
        {
            buffer_receive.crc_status = true;
        }
        return END;
    }
}


frame_state_t
DataLinkLayer::frame_end_received (char c)
{
    static uint8_t pos = 0;
    static char frame[2];
    frame[pos] = c;
    if(pos == 0) {
        pos++;
        return END;
    }
    else
    {
        if (!strncmp(frame,FRAME_END,2))
        {
            if (buffer_receive.crc_status)
            {
                buffer_receive.is_blocked = true;
                DataLinkLayer::status_send(ACK,true);
            }
            else
            {
                DataLinkLayer::status_send(ACK,false);
            }
        }
        else if (!strncmp(frame,STATUS_END,2))
        {
            if (buffer_send.ack_status)
            {
                buffer_send.is_blocked = false;
                //buffer_send.ack_status = false;
            }
        }
        buffer_send.ack_status = false;
        buffer_receive.crc_status = false;
        frame[0] = 0;
        frame[1] = 0;
        pos = 0;
        return START;
    }
}


bool
DataLinkLayer::frame_receive(void)
{
    static frame_state_t frame_state = START;
    char c;

    if(buffer_receive.is_blocked)
    {
        //return true;
    }

//    if(!port->ready_to_read())
//    {
//        return false;
//    }

    c = port->read_char();
    std::cout << c;

    switch ( frame_state ) {
        case DATA:
            // Reads the data frame
            frame_state = frame_data_received(c);
            break;
        case STATUS:
            // Reads the status frame
            frame_state = frame_status_received(c);
            break;
        case CRC:
            // Reads the status frame
            frame_state = frame_crc_received(c);
            break;
        case END:
            // Checks to see if the end frame received
            frame_state = frame_end_received(c);
            if(frame_state == START)
            {
                return true;
            }
            break;
        default:
            // Checks to see if the start frame received
            frame_state = frame_start_received(c);
            if(buffer_receive.is_blocked && frame_state == DATA)
            {
                frame_state = START;
                return true;
            }
            break;
    }
    return false;
}

void
DataLinkLayer::poll_data_link_layer (void)
{
// TODO : can send condition
//    if(!buffer_receive.other_side_blocked)
//    {
//        DataLinkLayer::frame_send();
//    }

    //DataLinkLayer::frame_send();
    //DataLinkLayer::status_send(STATUS,buffer_receive.is_blocked);
    for(int i = 0; i <POLL_SIZE; i++)
    {
        if(DataLinkLayer::frame_receive())
        {
            //break;
        }
    }
    std::cout << '\n';
}

bool
DataLinkLayer::query_data_link_layer (void)
{
// TODO : can send condition
    if(!buffer_receive.other_side_blocked)
    {
        DataLinkLayer::frame_send();
    }
    else
    {
        return false;
    }

    del.delay_ms(50);
    for(int i = 0; i <POLL_SIZE; i++)
    {
        if(DataLinkLayer::frame_receive())
        {
            //break;
        }
    }
    std::cout << '\n';
    return buffer_send.is_blocked;
}