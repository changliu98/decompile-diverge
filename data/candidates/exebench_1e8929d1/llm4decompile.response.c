void convert2ASCII(unsigned char input, unsigned char *output)
{
    unsigned char temp;

    temp = input >> 4;
    if (temp > 9)
        temp += 'a' - 10;
    else
        temp += '0';
    *output = temp;

    temp = input & 0x0f;
    if (temp > 9)
        temp += 'a' - 10;
    else
        temp += '0';
    *(output + 1) = temp;
}