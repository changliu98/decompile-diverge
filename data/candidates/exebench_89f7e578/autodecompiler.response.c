void put_num(char *buf, unsigned int n, unsigned char digits)
{
 if(digits >= 6) *(buf++) = ((n / 10000 % 10) + 16) | 0x2100;
 if(digits >= 5) *(buf++) = ((n / 1000 % 10) + 16) | 0x2100;
 if(digits >= 4) *(buf++) = ((n / 100 % 10) + 16) | 0x2100;
 if(digits >= 3) *(buf++) = ((n / 10 % 10) + 16) | 0x2100;
 if(digits >= 2) *(buf++) = ((n % 10) + 16) | 0x2100;
}