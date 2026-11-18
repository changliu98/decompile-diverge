uint32_t itoa(uint32_t value, char *str, uint32_t base)
{
    uint32_t idx_str = 0;
    uint32_t idx_digits;
    char digits[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char tmp[32];
    uint32_t idx_tmp = 0;

    if (base > 1 && base <= 36)
    {
        if (value == 0)
        {
            str[0] = '0';
            return 1;
        }

        while (value)
        {
            idx_digits = value % base;
            tmp[idx_tmp++] = digits[idx_digits];
            value /= base;
        }

        for (uint32_t i = 0; i < idx_tmp; i++)
        {
            str[idx_str++] = tmp[idx_tmp - i - 1];
        }

        return idx_str;
    }

    return 0;
}