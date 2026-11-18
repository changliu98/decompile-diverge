int UnpackImmediate(uint32_t value, uint32_t *byte, uint32_t *shift)
{
    int i;

    if (value == 0)
    {
        *byte = 0;
        *shift = 0;
        return 1;
    }

    for (i = 0; i < 15; i++)
    {
        if ((value & 0x3) != 0 && value <= 0xff)
        {
            *byte = value;
            *shift = i;
            return 1;
        }
        if ((value & 0x3) != 0)
            return 0;
        value >>= 2;
    }
    return 0;
}