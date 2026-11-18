int __cdecl vorbis_finish_frame(stb_vorbis *f, int len, int left, int right)
{
    int prev_len = f->previous_length;

    // Overlap-add with the previous frame if it exists
    if (prev_len > 0)
    {
        int n = prev_len;
        float *w = get_window(f, n);
        
        if (!w)
            return 0;

        for (int ch = 0; ch < f->channels; ++ch)
        {
            for (int i = 0; i < n; ++i)
            {
                float current = f->channel_buffers[ch][i + left] * w[i];
                float previous = f->previous_window[ch][i] * w[n - 1 - i];
                f->channel_buffers[ch][i + left] = current + previous;
            }
        }
    }

    // Update previous_length for the next frame
    f->previous_length = len - right;

    // Save the right side of the current frame to previous_window for the next overlap-add
    for (int ch = 0; ch < f->channels; ++ch)
    {
        for (int i = 0; i + right < len; ++i)
        {
            f->previous_window[ch][i] = f->channel_buffers[ch][i + right];
        }
    }

    // If there was no previous frame, no output is generated yet
    if (!prev_len)
        return 0;

    // Clamp right to the current frame length
    if (len < right)
        right = len;

    // Calculate and accumulate the number of output samples
    int samples_generated = right - left;
    f->samples_output += samples_generated;

    return samples_generated;
}