void noise_est(float *noise_gain, float gain, float up, float down, float min, float max)
{
    if(gain > *noise_gain + up)
    {
        *noise_gain += up;
    }
    else if(gain < *noise_gain + down)
    {
        *noise_gain += down;
    }
    else
    {
        *noise_gain = gain;
    }

    if(*noise_gain < min)
    {
        *noise_gain = min;
    }

    if(*noise_gain > max)
    {
        *noise_gain = max;
    }
}