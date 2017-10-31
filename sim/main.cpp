// Example program
#include <iostream>
#include <uart/uart_vt.h>
#include <stlm/data_link_layer/data_link.h>
#include <delay/delay_vt.h>
#include <thread>

#ifdef __RISC__
char type[] =  "RISC";
#endif

void test_uart_vt (void);
void test_dll (void);

int main()
{
    std::cout << "Hello this program is compiled for " << type << "\n";

    //test_uart_vt();
    test_dll();


    return 0;
}


void test_uart_vt (void)
{
    UartVirtual side_a;
    UartVirtual side_b;

    const char * a = "/tmp/tty.serialA";
    const char * b = "/tmp/tty.serialB";

    //    const char * a = "pipe1";
    //    const char * b = "pipe2";

    UartChannel channel(&side_a,&side_b);
    channel.open(a,b);

    side_a.write("beee", sizeof("beee"));
    std::cout << "Received : " << side_b.read_char() << "\n";
    std::cout << "Received : " << side_b.read_char() << "\n";
    std::cout << "Received : " << side_b.read_char() << "\n";
    std::cout << "Received : " << side_b.read_char() << "\n";
    std::cout << "Received : " << side_b.read_char() << "\n";



    channel.close();
}


void channel (DataLinkLayer * side_b)
{
    while (1)
    {
        char c[] = "Testdata";

        side_b->poll_data_link_layer();
        side_b->data_out(c,1);
    }
}

void test_dll (void)
{
    DataLinkLayer side_a;
    DataLinkLayer side_b;
    UartVirtual uart_a;
    UartVirtual uart_b;

    Delay del;

    side_a.attach_port(&uart_a);
    side_b.attach_port(&uart_b);

    const char * a = "/tmp/tty.serialA";
    const char * b = "/tmp/tty.serialB";
    UartChannel channel(&uart_a,&uart_b);
    channel.open(a,b);

    std::cout << "Channel started\n";
    //std::thread dd (channel,&side_b);

    del.delay_s(2);
    //sim.join();
    while (true)
    {
        char c[] = "Testdata";
        char d[20] = "Yoooooooo";
        bool e;

        std::cout << "Side A : " << side_a.data_in(c, strlen(c)) << '\n';
        side_a.query_data_link_layer();
        side_b.poll_data_link_layer();
        side_b.data_out(d, sizeof(d));
        std::cout << "Ack : " << !side_a.query_data_link_layer() << "\n";
        std::cout << "Received : " << d << "\n";
        del.delay_s(3);
    }
}