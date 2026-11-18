char *get_str(int a, int b, int c, int d)
{
    int total = 0;
    if (a > 0)
        total += a;
    if (b > 0)
        total += b;
    if (c > 0)
        total += c;
    if (d > 0)
        total += d;
    char *str = (char *)malloc((total + 1) * sizeof(char));
    if (str == ((void *)0))
    {
        perror("Failed to allocate memory");
        exit(1);
    }
    int i = 0;
    for (int j = 0; j < a; j++)
        str[i++] = 'p';
    for (int j = 0; j < b; j++)
        str[i++] = 'q';
    for (int j = 0; j < c; j++)
        str[i++] = 'r';
    for (int j = 0; j < d; j++)
        str[i++] = 's';
    str[i] = '\0';
    return str;
}