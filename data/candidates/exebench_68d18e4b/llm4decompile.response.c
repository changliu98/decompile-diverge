void SwitchToChar(unsigned char *str,unsigned char data)
{
    unsigned char temp;
    temp = data / 16;
    if(temp >= 10)
        temp = temp - 10 + 'a';
    else
        temp += '0';
    *str = temp;
    temp = data % 16;
    if(temp >= 10)
        temp = temp - 10 + 'a';
    else
        temp += '0';
    *(str+1) = temp;
}