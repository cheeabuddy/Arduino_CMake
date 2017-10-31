#include "uart_vt.h"



UartChannel::UartChannel (UartVirtual * sidea,UartVirtual * sideb)
{
    side_a = sidea;
    side_b = sideb;
}

void
UartChannel::open(const char * loca, const char * locb)
{
    side_a->set_port(loca);
    side_b->set_port(locb);

    side_a->open_port();
    side_b->open_port();

    side_a->create_channel(side_b->expose_port());
    side_b->create_channel(side_a->expose_port());
}

void
UartChannel::close(void)
{
    side_a->close_port();
    side_b->close_port();
}


void
UartVirtual::set_port(const char *pt)
{
    port_rx.location = pt;
}

void
UartVirtual::open_port(void)
{
    /* create the FIFO (named pipe) */
    mkfifo(port_rx.location, 0666);

    port_rx.instance = open(port_rx.location, O_RDONLY|O_NONBLOCK);
    if (port_rx.instance < 0) {fputs ("File error",stderr); exit (1);}
}

file_locator_t
UartVirtual::expose_port(void)
{
    return port_rx;
}

// requires location of the other port
void
UartVirtual::create_channel(file_locator_t pt)
{
    port_tx = pt;
    port_tx.instance = open(port_tx.location, O_WRONLY);
    if (port_tx.instance < 0) {fputs ("File error",stderr); exit (1);}
}

void
UartVirtual::close_port(void)
{
    close(port_rx.instance);
    /* remove the FIFO */
    unlink(port_rx.location);
}

char
UartVirtual::read_char(void)
{
    char c;
    ::read(port_rx.instance,&c,1);
    return c;
}

void
UartVirtual::put_char(char c)
{
    ::write(port_tx.instance,&c,1);
}

void
UartVirtual::write (const char * c, uint8_t length)
{
    ::write(port_tx.instance,c,length);
}

