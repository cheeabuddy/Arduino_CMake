#ifndef DATA_LINK_H
#define DATA_LINK_H

//#include "../settings.h"
#include <iostream>       // std::cout
#include <cstdint>      /* types */
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* calloc, exit, free */
#include <string.h>
#include "../../crc/crc.h"

#ifdef __RISC__
    #include <uart/uart_vt.h>
    #include <delay/delay_vt.h>
#endif

//#define FRAME_START "12"
//#define FRAME_END   "34"
#define BUFFER_SIZE 50
#define POLL_SIZE 50
#define crc_on 1
#define ack_on 1

typedef enum {
    START = 0,
    DATA,
    STATUS,
    ACK,
    CRC,
    END,
} frame_state_t;


typedef struct blocking_buffer
{
    char data[BUFFER_SIZE];
    bool is_blocked = false;
    bool other_side_blocked = false;
    bool ack_status = false;
    bool crc_status = false;

} blocking_buffer_t;

typedef struct status
{
    frame_state_t status_type;
    char result;
} status_t;

class DataLinkLayer
{
private:

    char FRAME_START[2] = {'$','1'};
    char FRAME_END[2] = {'$','2'};
    char STATUS_START[2] = {'$','3'};
    char STATUS_END[2] = {'$','4'};
    blocking_buffer_t buffer_send;
    blocking_buffer_t buffer_receive;
#ifdef __RISC__
    UartVirtual * port;
    Delay del;
#endif
    // framing functions
    frame_state_t frame_start_received (char c);
    frame_state_t frame_data_received (char c);
    frame_state_t frame_status_received (char c);
    frame_state_t frame_crc_received (char c);
    frame_state_t frame_end_received (char c);


    bool frame_send (void);
    bool frame_receive (void);
    bool status_send (frame_state_t status_type, bool state);
public:
    DataLinkLayer (void)
    {
        crcInit();
    }
#ifdef PC_ENVIRONMENT
    void attach_port (UartVirtual * prt);
#endif
    void poll_data_link_layer (void);
    bool query_data_link_layer (void);
    bool data_in (char * data, uint8_t length);
    bool data_out (char * data, uint8_t length);
    bool ready_to_send (void);
    bool ready_to_read (void);
};



#endif /* DATA_LINK_H */