void __cdecl InvSubBytes(BYTE (*state)[4])
{
    BYTE *p = (BYTE *)state;
    for (int i = 0; i < 16; ++i)
    {
        p[i] = aes_invsbox[p[i]];
    }
}