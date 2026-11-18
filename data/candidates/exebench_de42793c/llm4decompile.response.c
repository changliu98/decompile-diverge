int conv_hstring(char *string, u_int *num)
{
    int pos;

    *num = 0;
    for (pos = 0; ((string[pos] >= '0' && string[pos] <= '9') ||
                    (string[pos] >= 'a' && string[pos] <= 'f') ||
                    (string[pos] >= 'A' && string[pos] <= 'F')) &&
                   pos < 8; pos++)
        if (string[pos] >= '0' && string[pos] <= '9')
            *num = *num * 16 + string[pos] - '0';
        else
            *num = *num * 16 + string[pos] - 'a' + 10;

    return pos;
}