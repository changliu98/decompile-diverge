void __cdecl SubBytes(BYTE state[16])
{
    for (int i = 0; i < 16; i++) 
    {
        state[i] = aes_sbox[state[i]];
    }
}