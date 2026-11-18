void itoa(char *str, unsigned int num)
{
    char dig_array[11];
    int i;
    for(i = 0; i < 11; i++)
        dig_array[i] = '0';
    dig_array[10] = '\0';

    i = 9;
    while(num > 0)
    {
        int rem = num % 10;
        num /= 10;
        dig_array[i--] = rem + '0';
    }

    i = 0;
    while((dig_array[i] == '0') && (i < 10))
        i++;
    while(dig_array[i] != '\0')
        *(str++) = dig_array[i++];

    *str = '\0';
}