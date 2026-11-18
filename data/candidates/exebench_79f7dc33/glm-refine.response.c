void __cdecl bToHex0(char *pWrite, unsigned __int8 ch_0)
{
    pWrite[0] = a0123456789abcd[(ch_0 >> 4) & 0xF];
    pWrite[1] = a0123456789abcd[ch_0 & 0xF];
    pWrite[2] = '\0';
}