void util_word_to_dec(char *dst, unsigned int word)
{
    int i;
    char dig_array[11];

    for (i = 0; i < 10; i++)
        dig_array[i] = '0';
    dig_array[10] = 0;

    i = 9;
    while (word) {
        dig_array[i] = '0' + (word % 10);
        word /= 10;
        i--;
    }

    for (i = 0; dig_array[i] == '0' && i < 9; i++);

    while (dig_array[i]) {
        *dst = dig_array[i];
        i++;
        dst++;
    }
    *dst = 0;
}