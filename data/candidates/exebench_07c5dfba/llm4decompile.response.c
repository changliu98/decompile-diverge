void _itoa_dec(unsigned int val, char *buf)
{
    static const char *digits = "0123456789";
    unsigned int i;

    for (i = 0; i < 10; ++i) {
        if (val == 0 && i != 0) {
            buf[9 - i] = ' ';
        } else {
            buf[9 - i] = digits[val % 10];
        }
        val /= 10;
    }
}