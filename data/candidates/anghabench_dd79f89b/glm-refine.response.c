int __cdecl hx711_get_gain_to_pulse(int gain)
{
    // Assuming hx711_gain_to_scale is an array of structs or pairs.
    // If you have the actual struct definition, you can replace this.
    typedef struct {
        int gain;
        int pulse;
    } hx711_gain_scale_t;
    
    extern const hx711_gain_scale_t hx711_gain_to_scale[];

    for (int i = 0; i < HX711_GAIN_MAX; ++i)
    {
        if (hx711_gain_to_scale[i].gain == gain)
            return hx711_gain_to_scale[i].pulse;
    }
    return 1;
}