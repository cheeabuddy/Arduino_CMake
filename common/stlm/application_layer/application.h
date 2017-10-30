#ifndef APPLICATION_H
#define APPLICATION_H

//#include "../settings.h"
#include "../data_link_layer/data_link.h"

#define DATA_SIZE 30
#define OVERHEAD 3


typedef enum {
    DATA = 0,
    COMMAND,
} data_type_t;


typedef struct data_packet
{
    char data[DATA_SIZE];
    uint8_t length;
    uint8_t frame;
    data_type_t type;
} data_packet_t;


class ApplicationLayer : public DataLinkLayer
{
private:
    data_packet_t data_send;
    data_packet_t data_receive;
    void encode_data (void);
    void decode_data (void);
public:
    void data_in (const char * data, uint8_t length, uint8_t frame, packet_type_t type);
    void data_out (data_packet * data);
};


bool
ApplicationLayer::encode_data (void)
{
    char data[DATA_SIZE+OVERHEAD];

    strncpy((char *) &data_send.type,data[0],1);
    strncpy((char *) &data_send.frame,data[1],1);
    strncpy((char *) &data_send.length,data[2],1);
    strncpy(data_send.data,data[3],data_send.length);

    DataLinkLayer::data_in(data,data_send.length+OVERHEAD);
}

bool
ApplicationLayer::decode_data(void)
{
    char data[DATA_SIZE+OVERHEAD];
    char c;

    DataLinkLayer::data_out(data,DATA_SIZE+OVERHEAD);

    strncpy(data[0],c,1);
    data_receive.type = (data_type_t) c;
    strncpy(data[1],c,1);
    data_receive.frame = (uint8_t) c;
    strncpy(data[2],data_receive.length,1);
    data_receive.length = (uint8_t) c;
    strncpy(data[3],data_receive.data,data_recieve.length);
}

bool
ApplicationLayer::data_in (const char * data, uint8_t length, uint8_t frame, packet_type_t type)
{
    data_send =
            {
                    .length = length,
                    .frame = frame,
                    .type = type,
            };
    strncpy(data_send.data,data,length);
    return true;
}

bool
ApplicationLayer::data_out (data_type_t * data)
{
    &data = data_receive;

    return true;
}






bool
ApplicationLayer::data_in (const char * data, uint8_t length, uint8_t frame, packet_type_t type)
{
    data_send =
            {
                    .length = length,
                    .frame = frame,
                    .type = type,
            };
    strncpy(data_send.data,data,length);
    return true;
}


#endif /* APPLICATION_H */