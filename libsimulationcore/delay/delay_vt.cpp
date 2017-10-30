


#include "delay_vt.h"

void
Delay::set_fixed_delay(uint32_t delay)
{
    fixed_delay = delay;
}

void
Delay::delay_fixed (void)
{
    Delay::delay_m (fixed_delay);
}


void
Delay::delay_h (uint32_t delay)
{
    std::this_thread::sleep_for (std::chrono::hours(delay));
}

void
Delay::delay_m (uint32_t delay)
{
    std::this_thread::sleep_for (std::chrono::minutes(delay));
}

void
Delay::delay_s (uint32_t delay)
{
    std::this_thread::sleep_for (std::chrono::seconds(delay));
}

void
Delay::delay_ms (uint32_t delay)
{
    std::this_thread::sleep_for (std::chrono::milliseconds(delay));
}

void
Delay::delay_us (uint32_t delay)
{
    std::this_thread::sleep_for (std::chrono::microseconds(delay));
}

void
Delay::delay_ns (uint32_t delay)
{
    std::this_thread::sleep_for (std::chrono::nanoseconds(delay));
}