__attribute__((used)) static size_t sizeof_pwm_leds_priv(int num_leds)
{
    return sizeof(led_strip_t) + num_leds * sizeof(led_color_t);
}