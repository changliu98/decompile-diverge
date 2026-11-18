size_t sizeof_pwm_leds_priv(int num_leds)
{
    return sizeof(pwm_leds_priv) + num_leds * sizeof(pwm_led);
}