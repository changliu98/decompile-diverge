void drwav_s16_to_f32(int16_t *speech16b,
                         int16_t *speech8b,
                         size_t len)
{
    size_t i;
    if ((speech16b == NULL) || (speech8b == NULL))
    {
        return;
    }

    for (i = 0; i < len; i++)
    {

        *speech16b++ = (int16_t) ((float)speech8b[i] / 32768.0f);
    }
}