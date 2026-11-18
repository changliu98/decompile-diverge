void __cdecl mix_output_stereo(OPLL *opll)
{
    // Constants for better readability (assuming standard stereo channel mapping)
    const int LEFT = 0;
    const int RIGHT = 1;
    const int NUM_CHANNELS = 14;

    int16_t *mix_out = opll->mix_out;
    int32_t *ch_out = opll->ch_out;
    uint8_t *pan = opll->pan;
    float (*pan_fine)[2] = opll->pan_fine;

    // Initialize the mixing buffer
    mix_out[LEFT] = 0;
    mix_out[RIGHT] = 0;

    // Mix all channels into the stereo output buffer
    for (int i = 0; i < NUM_CHANNELS; ++i)
    {
        int32_t channel_signal = ch_out[i];

        // Check if the channel is panned to the left
        if (pan[i] & 2)
        {
            mix_out[LEFT] += (int)(channel_signal * pan_fine[i][LEFT]);
        }

        // Check if the channel is panned to the right
        if (pan[i] & 1)
        {
            mix_out[RIGHT] += (int)(channel_signal * pan_fine[i][RIGHT]);
        }
    }

    // If a sample rate converter is attached, feed the mixed samples to it
    if (opll->conv)
    {
        OPLL_RateConv_putData(opll->conv, LEFT, mix_out[LEFT]);
        OPLL_RateConv_putData(opll->conv, RIGHT, mix_out[RIGHT]);
    }
}