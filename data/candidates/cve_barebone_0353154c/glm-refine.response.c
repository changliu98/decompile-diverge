void __cdecl bit_write_UMC(Bit_Chain *dat, BITCODE_UMC val)
{
    unsigned __int8 byte[5];
    int i, j;

    // Step 1: Split the 32-bit integer into 5 chunks of 7 bits each.
    // The most significant chunks are at the lowest indices.
    for (i = 0, j = 28; i < 5; ++i, j -= 7) {
        byte[i] = (val >> j) & 0x7F;
        byte[i] |= 0x80; // Set the continuation bit
    }

    // Step 2: Find the first chunk that contains a non-zero value.
    for (i = 0; i < 4 && (byte[i] & 0x7F) == 0; ++i)
        ;

    // Step 3: If the sign bit (6th bit) of the first non-zero chunk is set,
    // step back one chunk to preserve the sign during decoding.
    if ((byte[i] & 0x40) != 0)
        --i;

    // Step 4: Clear the continuation bit on the last chunk to be written.
    byte[i] &= ~0x80u;

    // Step 5: Write the chunks from most significant to least significant.
    for (j = 4; j >= i; --j)
        bit_write_RC(dat, byte[j]);
}