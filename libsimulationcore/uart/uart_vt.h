#ifndef UART_VT_H
#define UART_VT_H

#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

class UartVirtual;

typedef struct file_locator
{
    const char * location;
    int instance;
}file_locator_t;

class UartChannel
{
private:
    UartVirtual * side_a;
    UartVirtual * side_b;
public:
    UartChannel (UartVirtual * sidea,UartVirtual * sideb);
    void open(const char * loca, const char * locb);
    void close(void);
};


void init_virtual_uart ();

class UartVirtual
{
private:
    file_locator_t port_tx;
    file_locator_t port_rx;
public:
    void set_port(const char * pt);
    void open_port (void);
    file_locator_t expose_port();
    void create_channel(file_locator_t pt);
    void close_port (void);
    char read_char (void);
    void put_char (char c);
    void write (const char * c, uint8_t length);
    bool ready_to_send (void);
    bool ready_to_read (void);
};



#endif //UART_VT_H
