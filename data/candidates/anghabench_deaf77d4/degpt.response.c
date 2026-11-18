/**
 * @brief Calculate the remaining time until the next counter overflow.
 *
 * This function computes the number of ticks remaining until the counter
 * wraps around (overflows). It assumes the counter is counting down or
 * that the calculation represents the distance to the overflow point.
 *
 * @param value The current counter value.
 * @return The number of ticks remaining until overflow.
 */
uint32_t pmc_sample_period(uint32_t current_counter_value)
{
    // Calculate the difference between the maximum counter value (overflow point)
    // and the current value to determine the remaining period.
    return (int)COUNTER_OVERFLOW - current_counter_value;
}