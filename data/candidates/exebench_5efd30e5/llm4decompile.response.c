int stringToInt(int *val, char *buff)
{
    *val = 0;
    while (*buff)
    {
        if (*buff < '0' || *buff > '9')
            return -1;
        *val = *val * 10 + *buff - '0';
        buff++;
    }
    return 0;
}