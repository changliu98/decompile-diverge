void swapIntEndian(int *pInteger)
{
    char *pByte = (char *)pInteger;
    char temp = pByte[0];
    pByte[0] = pByte[3];
    pByte[3] = temp;
    temp = pByte[1];
    pByte[1] = pByte[2];
    pByte[2] = temp;
}