void bToHex0(char *outputBuffer, uchar byteValue)
{
    outputBuffer[0] = "0123456789abcdef"[byteValue >> 4];
    outputBuffer[1] = "0123456789abcdef"[byteValue & 0xf];
    outputBuffer[2] = '\0';
}