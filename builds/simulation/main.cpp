// Example program
#include <iostream>

#ifdef __RISC__
  char type[] =  "RISC";
#endif


int main(void){

    std::cout << "Hello this program is compiled for " << type << "\n";
    return 0;
}
