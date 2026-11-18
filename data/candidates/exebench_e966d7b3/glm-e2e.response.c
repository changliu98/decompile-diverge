void MD5Transform(uint32_t state[4], const uint32_t block[16]) {
    uint32_t a = state[0];
    uint32_t b = state[1];
    uint32_t c = state[2];
    uint32_t d = state[3];

    // Round 1
    a = b + ROTATE_LEFT((a + ((b & c) ^ (~b & d)) + block[0]  + 0xd76aa478), 7);
    d = a + ROTATE_LEFT((d + ((a & b) ^ (~a & c)) + block[1]  + 0xe8c7b756), 12);
    c = d + ROTATE_LEFT((c + ((d & a) ^ (~d & b)) + block[2]  + 0x242070db), 17);
    b = c + ROTATE_LEFT((b + ((c & d) ^ (~c & a)) + block[3]  + 0xc1bdceee), 22);
    a = b + ROTATE_LEFT((a + ((b & c) ^ (~b & d)) + block[4]  + 0xf57c0faf), 7);
    d = a + ROTATE_LEFT((d + ((a & b) ^ (~a & c)) + block[5]  + 0x4787c62a), 12);
    c = d + ROTATE_LEFT((c + ((d & a) ^ (~d & b)) + block[6]  + 0xa8304613), 17);
    b = c + ROTATE_LEFT((b + ((c & d) ^ (~c & a)) + block[7]  + 0xfd469501), 22);
    a = b + ROTATE_LEFT((a + ((b & c) ^ (~b & d)) + block[8]  + 0x698098d8), 7);
    d = a + ROTATE_LEFT((d + ((a & b) ^ (~a & c)) + block[9]  + 0x8b44f7af), 12);
    c = d + ROTATE_LEFT((c + ((d & a) ^ (~d & b)) + block[10] + 0xffff5bb1), 17);
    b = c + ROTATE_LEFT((b + ((c & d) ^ (~c & a)) + block[11] + 0x895cd7be), 22);
    a = b + ROTATE_LEFT((a + ((b & c) ^ (~b & d)) + block[12] + 0x6b901122), 7);
    d = a + ROTATE_LEFT((d + ((a & b) ^ (~a & c)) + block[13] + 0xfd987193), 12);
    c = d + ROTATE_LEFT((c + ((d & a) ^ (~d & b)) + block[14] + 0xa679438e), 17);
    b = c + ROTATE_LEFT((b + ((c & d) ^ (~c & a)) + block[15] + 0x49b40821), 22);

    // Round 2
    a = b + ROTATE_LEFT((a + ((b & d) ^ (c & ~d)) + block[1]  + 0xf61e2562), 5);
    d = a + ROTATE_LEFT((d + ((a & c) ^ (b & ~c)) + block[6]  + 0xc040b340), 9);
    c = d + ROTATE_LEFT((c + ((d & b) ^ (a & ~b)) + block[11] + 0x265e5a51), 14);
    b = c + ROTATE_LEFT((b + ((c & a) ^ (d & ~a)) + block[0]  + 0xe9b6c7aa), 20);
    a = b + ROTATE_LEFT((a + ((b & d) ^ (c & ~d)) + block[5]  + 0xd62f105d), 5);
    d = a + ROTATE_LEFT((d + ((a & c) ^ (b & ~c)) + block[10] + 0x02441453), 9);
    c = d + ROTATE_LEFT((c + ((d & b) ^ (a & ~b)) + block[15] + 0xd8a1e681), 14);
    b = c + ROTATE_LEFT((b + ((c & a) ^ (d & ~a)) + block[4]  + 0xe7d3fbc8), 20);
    a = b + ROTATE_LEFT((a + ((b & d) ^ (c & ~d)) + block[9]  + 0x21e1cde6), 5);
    d = a + ROTATE_LEFT((d + ((a & c) ^ (b & ~c)) + block[14] + 0xc33707d6), 9);
    c = d + ROTATE_LEFT((c + ((d & b) ^ (a & ~b)) + block[3]  + 0xf4d50d87), 14);
    b = c + ROTATE_LEFT((b + ((c & a) ^ (d & ~a)) + block[8]  + 0x455a14ed), 20);
    a = b + ROTATE_LEFT((a + ((b & d) ^ (c & ~d)) + block[13] + 0xa9e3e905), 5);
    d = a + ROTATE_LEFT((d + ((a & c) ^ (b & ~c)) + block[2]  + 0xfcefa3f8), 9);
    c = d + ROTATE_LEFT((c + ((d & b) ^ (a & ~b)) + block[7]  + 0x676f02d9), 14);
    b = c + ROTATE_LEFT((b + ((c & a) ^ (d & ~a)) + block[12] + 0x8d2a4c8a), 20);

    // Round 3
    a = b + ROTATE_LEFT((a + (b ^ c ^ d) + block[5]  + 0xfffa3942), 4);
    d = a + ROTATE_LEFT((d + (a ^ b ^ c) + block[8]  + 0x8771f681), 11);
    c = d + ROTATE_LEFT((c + (d ^ a ^ b) + block[11] + 0x6d9d6122), 16);
    b = c + ROTATE_LEFT((b + (c ^ d ^ a) + block[14] + 0xfde5380c), 23);
    a = b + ROTATE_LEFT((a + (b ^ c ^ d) + block[1]  + 0xa4beea44), 4);
    d = a + ROTATE_LEFT((d + (a ^ b ^ c) + block[4]  + 0x4bdecfa9), 11);
    c = d + ROTATE_LEFT((c + (d ^ a ^ b) + block[7]  + 0xf6bb4b60), 16);
    b = c + ROTATE_LEFT((b + (c ^ d ^ a) + block[10] + 0xbebfbc70), 23);
    a = b + ROTATE_LEFT((a + (b ^ c ^ d) + block[13] + 0x289b7ec6), 4);
    d = a + ROTATE_LEFT((d + (a ^ b ^ c) + block[0]  + 0xeaa127fa), 11);
    c = d + ROTATE_LEFT((c + (d ^ a ^ b) + block[3]  + 0xd4ef3085), 16);
    b = c + ROTATE_LEFT((b + (c ^ d ^ a) + block[6]  + 0x04881d05), 23);
    a = b + ROTATE_LEFT((a + (b ^ c ^ d) + block[9]  + 0xd9d4d039), 4);
    d = a + ROTATE_LEFT((d + (a ^ b ^ c) + block[12] + 0xe6db99e5), 11);
    c = d + ROTATE_LEFT((c + (d ^ a ^ b) + block[15] + 0x1fa27cf8), 16);
    b = c + ROTATE_LEFT((b + (c ^ d ^ a) + block[2]  + 0xc4ac5665), 23);

    // Round 4
    a = b + ROTATE_LEFT((a + (c ^ (b | ~d)) + block[0]  + 0xf4292244), 6);
    d = a + ROTATE_LEFT((d + (b ^ (a | ~c)) + block[7]  + 0x432aff97), 10);
    c = d + ROTATE_LEFT((c + (a ^ (d | ~b)) + block[14] + 0xab9423a7), 15);
    b = c + ROTATE_LEFT((b + (d ^ (c | ~a)) + block[5]  + 0xfc93a039), 21);
    a = b + ROTATE_LEFT((a + (c ^ (b | ~d)) + block[12] + 0x655b59c3), 6);
    d = a + ROTATE_LEFT((d + (b ^ (a | ~c)) + block[3]  + 0x8f0ccc92), 10);
    c = d + ROTATE_LEFT((c + (a ^ (d | ~b)) + block[10] + 0xffeff47d), 15);
    b = c + ROTATE_LEFT((b + (d ^ (c | ~a)) + block[1]  + 0x85845dd1), 21);
    a = b + ROTATE_LEFT((a + (c ^ (b | ~d)) + block[8]  + 0x6fa87e4f), 6);
    d = a + ROTATE_LEFT((d + (b ^ (a | ~c)) + block[15] + 0xfe2ce6e0), 10);
    c = d + ROTATE_LEFT((c + (a ^ (d | ~b)) + block[6]  + 0xa3014314), 15);
    b = c + ROTATE_LEFT((b + (d ^ (c | ~a)) + block[13] + 0x4e0811a1), 21);
    a = b + ROTATE_LEFT((a + (c ^ (b | ~d)) + block[4]  + 0xf7537e82), 6);
    d = a + ROTATE_LEFT((d + (b ^ (a | ~c)) + block[11] + 0xbd3af235), 10);
    c = d + ROTATE_LEFT((c + (a ^ (d | ~b)) + block[2]  + 0x2ad7d2bb), 15);
    b = c + ROTATE_LEFT((b + (d ^ (c | ~a)) + block[9]  + 0xeb86d391), 21);

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}