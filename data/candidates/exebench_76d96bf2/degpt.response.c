void goertzel_filter_v1(short *samples, short new_sample, short gain_factor)
{
    // Shift the previous delay values to make room for the new sample
    samples[2] = samples[1];
    
    // Calculate the current output sample using the Goertzel algorithm's difference equation
    // The input is scaled down by 7 bits, the product is scaled down by 14 bits,
    // and the result is accumulated with the previous state and subtracted by the oldest sample
    samples[1] = (new_sample >> 7) + ((samples[1] * gain_factor) >> 14) - samples[2];
}