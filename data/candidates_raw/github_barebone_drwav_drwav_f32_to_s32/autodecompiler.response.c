void WebRtcPcm16b_EncodeW16FromFloat(int16_t *speech16b,
                                     float *speechIn16b,
                                     size_t len)
{
    size_t i;
    if ((speech16b == NULL) || (speechIn16b == NULL))
    {
        return;
    }

    for (i = 0; i < len; i++)
    {
        speech16b[i] = (int16_t) (speechIn16b[i] * 32768.f);
    }
}