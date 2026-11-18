void IntToHex(char *pWrite, char Value)
{
    char *hex = "0123456789abcdef";
    pWrite[0] = hex[(Value >> 4) & 0x0f];
    pWrite[1] = hex[Value & 0x0f];
    pWrite[2] = '\0';
}