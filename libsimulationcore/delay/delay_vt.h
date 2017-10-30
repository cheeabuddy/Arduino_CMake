#ifndef HW_PC_DELAY_H
#define HW_PC_DELAY_H


#include <cstdint>      /* types */
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* calloc, exit, free */
#include <chrono>
#include <thread>

class Delay
{
private:
    uint32_t fixed_delay;
public:
    void set_fixed_delay (uint32_t delay);
    void delay_fixed (void); // only in ms atm
    void delay_h (uint32_t delay);
    void delay_m (uint32_t delay);
    void delay_s (uint32_t delay);
    void delay_ms (uint32_t delay);
    void delay_us (uint32_t delay);
    void delay_ns (uint32_t delay);

};


#endif /* HW_PC_DELAY_H */