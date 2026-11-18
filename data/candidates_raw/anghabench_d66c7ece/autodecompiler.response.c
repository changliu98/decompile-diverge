__attribute__((used)) static size_t _led_strip_get_buffer_size(int num_leds)
{
    return sizeof(led_strip_t) + num_leds * sizeof(led_color_t);
}