__attribute__((used)) static size_t sizeof_ns2_led_priv(int num_leds)
{
    return sizeof(led_strip_t) + num_leds * sizeof(led_color_t);
}