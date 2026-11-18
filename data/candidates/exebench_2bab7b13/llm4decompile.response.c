void Swap8Bytes(char *bytes)
{
    char temp;
    temp = bytes[0];
    bytes[0] = bytes[7];
    bytes[7] = temp;
    temp = bytes[1];
    bytes[1] = bytes[6];
    bytes[6] = temp;
    temp = bytes[2];
    bytes[2] = bytes[5];
    bytes[5] = temp;
    temp = bytes[3];
    bytes[3] = bytes[4];
    bytes[4] = temp;
}