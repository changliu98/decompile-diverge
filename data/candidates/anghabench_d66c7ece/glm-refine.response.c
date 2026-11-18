size_t sizeof_pwm_leds_priv(int num_leds)
{
    return (sizeof(int) * num_leds) + sizeof(int);
}