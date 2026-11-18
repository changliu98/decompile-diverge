void Swap8Bytes(char *str)
{
 char tmp;
 tmp = str[0];
 str[0] = str[7];
 str[7] = tmp;
 tmp = str[1];
 str[1] = str[6];
 str[6] = tmp;
 tmp = str[2];
 str[2] = str[5];
 str[5] = tmp;
 tmp = str[3];
 str[3] = str[4];
 str[4] = tmp;
}