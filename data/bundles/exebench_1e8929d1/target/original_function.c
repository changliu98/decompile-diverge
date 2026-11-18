static void convert2ASCII(char input, char *output)
{
    unsigned char temp = input >> 4;
    if (temp < 10)
 output[0] = temp + '0';
    else
 output[0] = temp - 10 + 'a';
    input &= 0xf;
    if (input < 10)
 output[1] = input + '0';
    else
 output[1] = input - 10 + 'a';
}