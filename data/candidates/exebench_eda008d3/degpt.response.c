void arx_bwd(uchar *block)
{
    // Rotate state[2] right by 4 bits
    block[2] = block[2] << 4 | (byte)((int)(uint)block[2] >> 4);
    // XOR state[1] with state[2]
    block[1] = block[1] ^ block[2];
    // XOR state[3] with state[0] (dereferenced pointer)
    block[3] = block[3] ^ *block;
    // Rotate state[1] right by 3 bits (left shift 5)
    block[1] = block[1] << 5 | (byte)((int)(uint)block[1] >> 3);
    // Rotate state[3] right by 7 bits (left shift 1)
    block[3] = block[3] << 1 | (byte)((int)(uint)block[3] >> 7);
    // Subtract state[3] from state[0]
    *block = *block - block[3];
    // Subtract state[1] from state[2]
    block[2] = block[2] - block[1];
    // Rotate state[0] right by 4 bits
    *block = *block << 4 | (byte)((int)(uint)*block >> 4);
    // XOR state[1] with state[0]
    block[1] = block[1] ^ *block;
    // XOR state[3] with state[2]
    block[3] = block[3] ^ block[2];
    // Rotate state[1] right by 2 bits (left shift 6)
    block[1] = block[1] << 6 | (byte)((int)(uint)block[1] >> 2);
    // Rotate state[3] right by 5 bits (left shift 3)
    block[3] = block[3] << 3 | (byte)((int)(uint)block[3] >> 5);
    // Subtract state[1] from state[0]
    *block = *block - block[1];
    // Subtract state[3] from state[2]
    block[2] = block[2] - block[3];
}