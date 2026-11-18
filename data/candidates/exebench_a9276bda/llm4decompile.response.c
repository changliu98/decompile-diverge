char *intToString(char *buff, uint32_t val)
{
    int i;
    buff[9] = 0;
    for (i = 8; i >= 0; i--) {
        buff[i] = '0' + (val % 10);
        val /= 10;
        if (val == 0)
            break;
    }
    return buff + i;
}