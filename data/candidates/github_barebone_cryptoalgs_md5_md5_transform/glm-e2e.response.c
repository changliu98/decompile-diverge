void md5_transform(struct MD5_CTX *ctx, const uint8_t *data) {
    uint32_t M[16];
    uint32_t a, b, c, d;

    // Unpack 64 bytes of data into 16 32-bit little-endian words
    for (int i = 0; i < 16; i++) {
        M[i] = (uint32_t)data[i * 4] |
               ((uint32_t)data[i * 4 + 1] << 8) |
               ((uint32_t)data[i * 4 + 2] << 16) |
               ((uint32_t)data[i * 4 + 3] << 24);
    }

    // Initialize a, b, c, d to the current state
    a = ctx->state[0]; // ctx + 0x50
    b = ctx->state[1]; // ctx + 0x54
    c = ctx->state[2]; // ctx + 0x58
    d = ctx->state[3]; // ctx + 0x5c

    // Round 1
    a = b + ((a + ((b & c) | (~b & d)) + M[0]  + 0xd76aa478)  << 7  | (a + ((b & c) | (~b & d)) + M[0]  + 0xd76aa478)  >> 25);
    d = a + ((d + ((a & b) | (~a & c)) + M[1]  + 0xe8c7b756)  << 12 | (d + ((a & b) | (~a & c)) + M[1]  + 0xe8c7b756)  >> 20);
    c = d + ((c + ((d & a) | (~d & b)) + M[2]  + 0x242070db)  << 17 | (c + ((d & a) | (~d & b)) + M[2]  + 0x242070db)  >> 15);
    b = c + ((b + ((c & d) | (~c & a)) + M[3]  + 0xc1bdceee)  << 22 | (b + ((c & d) | (~c & a)) + M[3]  + 0xc1bdceee)  >> 10);
    a = b + ((a + ((b & c) | (~b & d)) + M[4]  + 0xf57c0faf)  << 7  | (a + ((b & c) | (~b & d)) + M[4]  + 0xf57c0faf)  >> 25);
    d = a + ((d + ((a & b) | (~a & c)) + M[5]  + 0x4787c62a)  << 12 | (d + ((a & b) | (~a & c)) + M[5]  + 0x4787c62a)  >> 20);
    c = d + ((c + ((d & a) | (~d & b)) + M[6]  + 0xa8304613)  << 17 | (c + ((d & a) | (~d & b)) + M[6]  + 0xa8304613)  >> 15);
    b = c + ((b + ((c & d) | (~c & a)) + M[7]  + 0xfd469501)  << 22 | (b + ((c & d) | (~c & a)) + M[7]  + 0xfd469501)  >> 10);
    a = b + ((a + ((b & c) | (~b & d)) + M[8]  + 0x698098d8)  << 7  | (a + ((b & c) | (~b & d)) + M[8]  + 0x698098d8)  >> 25);
    d = a + ((d + ((a & b) | (~a & c)) + M[9]  + 0x8b44f7af)  << 12 | (d + ((a & b) | (~a & c)) + M[9]  + 0x8b44f7af)  >> 20);
    c = d + ((c + ((d & a) | (~d & b)) + M[10] + 0xffff5bb1)  << 17 | (c + ((d & a) | (~d & b)) + M[10] + 0xffff5bb1)  >> 15);
    b = c + ((b + ((c & d) | (~c & a)) + M[11] + 0x895cd7be)  << 22 | (b + ((c & d) | (~c & a)) + M[11] + 0x895cd7be)  >> 10);
    a = b + ((a + ((b & c) | (~b & d)) + M[12] + 0x6b901122)  << 7  | (a + ((b & c) | (~b & d)) + M[12] + 0x6b901122)  >> 25);
    d = a + ((d + ((a & b) | (~a & c)) + M[13] + 0xfd987193)  << 12 | (d + ((a & b) | (~a & c)) + M[13] + 0xfd987193)  >> 20);
    c = d + ((c + ((d & a) | (~d & b)) + M[14] + 0xa679438e)  << 17 | (c + ((d & a) | (~d & b)) + M[14] + 0xa679438e)  >> 15);
    b = c + ((b + ((c & d) | (~c & a)) + M[15] + 0x49b40821)  << 22 | (b + ((c & d) | (~c & a)) + M[15] + 0x49b40821)  >> 10);

    // Round 2
    a = b + ((a + ((b & d) | (c & ~d)) + M[1]  + 0xf61e2562)  << 5  | (a + ((b & d) | (c & ~d)) + M[1]  + 0xf61e2562)  >> 27);
    d = a + ((d + ((a & c) | (b & ~c)) + M[6]  + 0xc040b340)  << 9  | (d + ((a & c) | (b & ~c)) + M[6]  + 0xc040b340)  >> 23);
    c = d + ((c + ((d & b) | (a & ~b)) + M[11] + 0x265e5a51)  << 14 | (c + ((d & b) | (a & ~b)) + M[11] + 0x265e5a51)  >> 18);
    b = c + ((b + ((c & a) | (d & ~a)) + M[0]  + 0xe9b6c7aa)  << 20 | (b + ((c & a) | (d & ~a)) + M[0]  + 0xe9b6c7aa)  >> 12);
    a = b + ((a + ((b & d) | (c & ~d)) + M[5]  + 0xd62f105d)  << 5  | (a + ((b & d) | (c & ~d)) + M[5]  + 0xd62f105d)  >> 27);
    d = a + ((d + ((a & c) | (b & ~c)) + M[10] + 0x02441453)  << 9  | (d + ((a & c) | (b & ~c)) + M[10] + 0x02441453)  >> 23);
    c = d + ((c + ((d & b) | (a & ~b)) + M[15] + 0xd8a1e681)  << 14 | (c + ((d & b) | (a & ~b)) + M[15] + 0xd8a1e681)  >> 18);
    b = c + ((b + ((c & a) | (d & ~a)) + M[4]  + 0xe7d3fbc8)  << 20 | (b + ((c & a) | (d & ~a)) + M[4]  + 0xe7d3fbc8)  >> 12);
    a = b + ((a + ((b & d) | (c & ~d)) + M[9]  + 0x21e1cde6)  << 5  | (a + ((b & d) | (c & ~d)) + M[9]  + 0x21e1cde6)  >> 27);
    d = a + ((d + ((a & c) | (b & ~c)) + M[14] + 0xc33707d6)  << 9  | (d + ((a & c) | (b & ~c)) + M[14] + 0xc33707d6)  >> 23);
    c = d + ((c + ((d & b) | (a & ~b)) + M[3]  + 0xf4d50d87)  << 14 | (c + ((d & b) | (a & ~b)) + M[3]  + 0xf4d50d87)  >> 18);
    b = c + ((b + ((c & a) | (d & ~a)) + M[8]  + 0x455a14ed)  << 20 | (b + ((c & a) | (d & ~a)) + M[8]  + 0x455a14ed)  >> 12);
    a = b + ((a + ((b & d) | (c & ~d)) + M[13] + 0xa9e3e905)  << 5  | (a + ((b & d) | (c & ~d)) + M[13] + 0xa9e3e905)  >> 27);
    d = a + ((d + ((a & c) | (b & ~c)) + M[2]  + 0xfcefa3f8)  << 9  | (d + ((a & c) | (b & ~c)) + M[2]  + 0xfcefa3f8)  >> 23);
    c = d + ((c + ((d & b) | (a & ~b)) + M[7]  + 0x676f02d9)  << 14 | (c + ((d & b) | (a & ~b)) + M[7]  + 0x676f02d9)  >> 18);
    b = c + ((b + ((c & a) | (d & ~a)) + M[12] + 0x8d2a4c8a)  << 20 | (b + ((c & a) | (d & ~a)) + M[12] + 0x8d2a4c8a)  >> 12);

    // Round 3
    a = b + ((a + (b ^ c ^ d) + M[5]  + 0xfffa3942)  << 4  | (a + (b ^ c ^ d) + M[5]  + 0xfffa3942)  >> 28);
    d = a + ((d + (a ^ b ^ c) + M[8]  + 0x8771f681)  << 11 | (d + (a ^ b ^ c) + M[8]  + 0x8771f681)  >> 21);
    c = d + ((c + (d ^ a ^ b) + M[11] + 0x6d9d6122)  << 16 | (c + (d ^ a ^ b) + M[11] + 0x6d9d6122)  >> 16);
    b = c + ((b + (c ^ d ^ a) + M[14] + 0xfde5380c)  << 23 | (b + (c ^ d ^ a) + M[14] + 0xfde5380c)  >> 9);
    a = b + ((a + (b ^ c ^ d) + M[1]  + 0xa4beea44)  << 4  | (a + (b ^ c ^ d) + M[1]  + 0xa4beea44)  >> 28);
    d = a + ((d + (a ^ b ^ c) + M[4]  + 0x4bdecfa9)  << 11 | (d + (a ^ b ^ c) + M[4]  + 0x4bdecfa9)  >> 21);
    c = d + ((c + (d ^ a ^ b) + M[7]  + 0xf6bb4b60)  << 16 | (c + (d ^ a ^ b) + M[7]  + 0xf6bb4b60)  >> 16);
    b = c + ((b + (c ^ d ^ a) + M[10] + 0xbebfbc70)  << 23 | (b + (c ^ d ^ a) + M[10] + 0xbebfbc70)  >> 9);
    a = b + ((a + (b ^ c ^ d) + M[13] + 0x289b7ec6)  << 4  | (a + (b ^ c ^ d) + M[13] + 0x289b7ec6)  >> 28);
    d = a + ((d + (a ^ b ^ c) + M[0]  + 0xeaa127fa)  << 11 | (d + (a ^ b ^ c) + M[0]  + 0xeaa127fa)  >> 21);
    c = d + ((c + (d ^ a ^ b) + M[3]  + 0xd4ef3085)  << 16 | (c + (d ^ a ^ b) + M[3]  + 0xd4ef3085)  >> 16);
    b = c + ((b + (c ^ d ^ a) + M[6]  + 0x04881d05)  << 23 | (b + (c ^ d ^ a) + M[6]  + 0x04881d05)  >> 9);
    a = b + ((a + (b ^ c ^ d) + M[9]  + 0xd9d4d039)  << 4  | (a + (b ^ c ^ d) + M[9]  + 0xd9d4d039)  >> 28);
    d = a + ((d + (a ^ b ^ c) + M[12] + 0xe6db99e5)  << 11 | (d + (a ^ b ^ c) + M[12] + 0xe6db99e5)  >> 21);
    c = d + ((c + (d ^ a ^ b) + M[15] + 0x1fa27cf8)  << 16 | (c + (d ^ a ^ b) + M[15] + 0x1fa27cf8)  >> 16);
    b = c + ((b + (c ^ d ^ a) + M[2]  + 0xc4ac5665)  << 23 | (b + (c ^ d ^ a) + M[2]  + 0xc4ac5665)  >> 9);

    // Round 4
    a = b + ((a + (c ^ (b | ~d)) + M[0]  + 0xf4292244)  << 6  | (a + (c ^ (b | ~d)) + M[0]  + 0xf4292244)  >> 26);
    d = a + ((d + (b ^ (a | ~c)) + M[7]  + 0x432aff97)  << 10 | (d + (b ^ (a | ~c)) + M[7]  + 0x432aff97)  >> 22);
    c = d + ((c + (a ^ (d | ~b)) + M[14] + 0xab9423a7)  << 15 | (c + (a ^ (d | ~b)) + M[14] + 0xab9423a7)  >> 17);
    b = c + ((b + (d ^ (c | ~a)) + M[5]  + 0xfc93a039)  << 21 | (b + (d ^ (c | ~a)) + M[5]  + 0xfc93a039)  >> 11);
    a = b + ((a + (c ^ (b | ~d)) + M[12] + 0x655b59c3)  << 6  | (a + (c ^ (b | ~d)) + M[12] + 0x655b59c3)  >> 26);
    d = a + ((d + (b ^ (a | ~c)) + M[3]  + 0x8f0ccc92)  << 10 | (d + (b ^ (a | ~c)) + M[3]  + 0x8f0ccc92)  >> 22);
    c = d + ((c + (a ^ (d | ~b)) + M[10] + 0xffeff47d)  << 15 | (c + (a ^ (d | ~b)) + M[10] + 0xffeff47d)  >> 17);
    b = c + ((b + (d ^ (c | ~a)) + M[1]  + 0x85845dd1)  << 21 | (b + (d ^ (c | ~a)) + M[1]  + 0x85845dd1)  >> 11);
    a = b + ((a + (c ^ (b | ~d)) + M[8]  + 0x6fa87e4f)  << 6  | (a + (c ^ (b | ~d)) + M[8]  + 0x6fa87e4f)  >> 26);
    d = a + ((d + (b ^ (a | ~c)) + M[15] + 0xfe2ce6e0)  << 10 | (d + (b ^ (a | ~c)) + M[15] + 0xfe2ce6e0)  >> 22);
    c = d + ((c + (a ^ (d | ~b)) + M[6]  + 0xa3014314)  << 15 | (c + (a ^ (d | ~b)) + M[6]  + 0xa3014314)  >> 17);
    b = c + ((b + (d ^ (c | ~a)) + M[13] + 0x4e0811a1)  << 21 | (b + (d ^ (c | ~a)) + M[13] + 0x4e0811a1)  >> 11);
    a = b + ((a + (c ^ (b | ~d)) + M[4]  + 0xf7537e82)  << 6  | (a + (c ^ (b | ~d)) + M[4]  + 0xf7537e82)  >> 26);
    d = a + ((d + (b ^ (a | ~c)) + M[11] + 0xbd3af235)  << 10 | (d + (b ^ (a | ~c)) + M[11] + 0xbd3af235)  >> 22);
    c = d + ((c + (a ^ (d | ~b)) + M[2]  + 0x2ad7d2bb)  << 15 | (c + (a ^ (d | ~b)) + M[2]  + 0x2ad7d2bb)  >> 17);
    b = c + ((b + (d ^ (c | ~a)) + M[9]  + 0xeb86d391)  << 21 | (b + (d ^ (c | ~a)) + M[9]  + 0xeb86d391)  >> 11);

    // Update the context state
    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
}