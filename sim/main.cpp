// Example program
#include <iostream>
#include <uart/uart_vt.h>
#include <crc/crc.h>

#ifdef __RISC__
char type[] =  "RISC";
#endif

int main()
{
    std::cout << "Hello this program is compiled for " << type << "\n";

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


    return 0;
}
