int __cdecl sizeof_ns2_led_priv(int num_leds)
{
    const int element_size = 4;
    const int header_size = 4;
    
    return (num_leds * element_size) + header_size;
}