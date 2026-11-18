int ff_rescale_rms(int rms, int energy)
{
    return (int64_t)rms * energy >> 10;
}