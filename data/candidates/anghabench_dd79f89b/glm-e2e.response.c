int hx711_get_gain_to_pulse(int gain) {
    int pulse = 1; // Default value if not found (initialized at 0x121e)
    int i = 0;

    while (i < HX711_GAIN_MAX) {
        if (hx711_gain_to_scale[i][0] == gain) {
            pulse = hx711_gain_to_scale[i][1];
            break;
        }
        i++;
    }
    
    return pulse;
}