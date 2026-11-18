void __cdecl MD5Transform(unsigned int *buf, const unsigned int *in)
{
    unsigned int a = buf[0];
    unsigned int b = buf[1];
    unsigned int c = buf[2];
    unsigned int d = buf[3];

    // Round 1: F(b, c, d) = (d ^ c) & b ^ d
    a = b + LEFTROTATE(a + in[0]  + ((d ^ c) & b ^ d) - 680876936,  7);
    d = a + LEFTROTATE(d + in[1]  + ((c ^ b) & a ^ c) - 389564586, 12);
    c = a + LEFTROTATE(c + in[2]  + ((b ^ a) & d ^ b) + 606105819, 17);
    b = d + LEFTROTATE(b + in[3]  + ((a ^ d) & c ^ a) - 1044525330, 22);
    a = b + LEFTROTATE(a + in[4]  + ((d ^ c) & b ^ d) - 176418897,  7);
    d = a + LEFTROTATE(d + in[5]  + ((c ^ b) & a ^ c) + 1200080426, 12);
    c = a + LEFTROTATE(c + in[6]  + ((b ^ a) & d ^ b) - 1473231341, 17);
    b = d + LEFTROTATE(b + in[7]  + ((a ^ d) & c ^ a) - 45705983,   22);
    a = b + LEFTROTATE(a + in[8]  + ((d ^ c) & b ^ d) + 1770035416,  7);
    d = a + LEFTROTATE(d + in[9]  + ((c ^ b) & a ^ c) - 1958414417, 12);
    c = a + LEFTROTATE(c + in[10] + ((b ^ a) & d ^ b) - 42063,      17);
    b = d + LEFTROTATE(b + in[11] + ((a ^ d) & c ^ a) - 1990404162, 22);
    a = b + LEFTROTATE(a + in[12] + ((d ^ c) & b ^ d) + 1804603682,  7);
    d = a + LEFTROTATE(d + in[13] + ((c ^ b) & a ^ c) - 40341101,   12);
    c = a + LEFTROTATE(c + in[14] + ((b ^ a) & d ^ b) - 1502002290, 17);
    b = d + LEFTROTATE(b + in[15] + ((a ^ d) & c ^ a) + 1236535329, 22);

    // Round 2: G(b, c, d) = (c ^ d) & b ^ c  (Obfuscated in original as (b ^ d) & c ^ b)
    a = b + LEFTROTATE(a + in[1]  + ((c ^ bh) & d ^ c) - 165796510,  5);
    d = a + LEFTROTATE(d + in[6]  + ((b ^ a) & c ^ b) - 1069501632,  9);
    c = a + LEFTROTATE(c + in[11] + ((a ^ d) & b ^ a) + 643717713,  14);
    b = d + LEFTROTATE(b + in[0]  + ((d ^ c) & a ^ d) - 373897302,  20);
    a = b + LEFTROTATE(a + in[5]  + ((c ^ bh) & d ^ c) - 701558691,  5);
    d = a + LEFTROTATE(d + in[10] + ((b ^ a) & c ^ b) + 38016083,    9);
    c = a + LEFTROTATE(c + in[15] + ((a ^ d) & b ^ a) - 660478335,  14);
    b = d + LEFTROTATE(b + in[4]  + ((d ^ c) & a ^ d) - 405537848,  20);
    a = b + LEFTROTATE(a + in[9]  + ((c ^ bh) & d ^ c) + 568446438,  5);
    d = a + LEFTROTATE(d + in[14] + ((b ^ a) & c ^ b) - 1019803690,  9);
    c = a + LEFTROTATE(c + in[3]  + ((a ^ d) & b ^ a) - 187363961,  14);
    b = d + LEFTROTATE(b + in[8]  + ((d ^ c) & a ^ d) + 1163531501, 20);
    a = b + LEFTROTATE(a + in[13] + ((c ^ bh) & d ^ c) - 1444681467, 5);
    d = a + LEFTROTATE(d + in[2]  + ((b ^ a) & c ^ b) - 51403784,    9);
    c = a + LEFTROTATE(c + in[7]  + ((a ^ d) & b ^ a) + 1735328473, 14);
    b = d + LEFTROTATE(b + in[12] + ((d ^ c) & a ^ d) - 1926607734, 20);

    // Round 3: H(b, c, d) = b ^ c ^ d
    a = b + LEFTROTATE(a + in[5]  + (d ^ c ^ b) - 378558,            4);
    d = a + LEFTROTATE(d + in[8]  + (c ^ b ^ a) - 2022574463,       11);
    c = a + LEFTROTATE(c + in[11] + (b ^ a ^ d) + 1839030562,       16);
    b = d + LEFTROTATE(b + in[14] + (a ^ d ^ c) - 35309556,         23);
    a = b + LEFTROTATE(a + in[1]  + (d ^ c ^ b) - 1530992060,        4);
    d = a + LEFTROTATE(d + in[4]  + (c ^ b ^ a) + 1272893353,       11);
    c = a + LEFTROTATE(c + in[7]  + (b ^ a ^ d) - 155497632,        16);
    b = d + LEFTROTATE(b + in[10] + (a ^ d ^ c) - 1094730640,       23);
    a = b + LEFTROTATE(a + in[13] + (d ^ c ^ b) + 681279174,         4);
    d = a + LEFTROTATE(d + in[0]  + (c ^ b ^ a) - 358537222,        11);
    c = a + LEFTROTATE(c + in[3]  + (b ^ a ^ d) - 722521979,        16);
    b = d + LEFTROTATE(b + in[6]  + (a ^ d ^ c) + 76029189,         23);
    a = b + LEFTROTATE(a + in[9]  + (d ^ c ^ b) - 640364487,         4);
    d = a + LEFTROTATE(d + in[12] + (c ^ b ^ a) - 421815835,        11);
    c = a + LEFTROTATE(c + in[15] + (b ^ a ^ d) + 530742520,        16);
    b = d + LEFTROTATE(b + in[2]  + (a ^ d ^ c) - 995338651,        23);

    // Round 4: I(b, c, d) = c ^ (~d | b)  (Obfuscated in original as (~d | b) ^ c)
    a = b + LEFTROTATE(a + in[0]  + (c ^ (~d | b)) - 198630844,      6);
    d = a + LEFTROTATE(d + in[7]  + (b ^ (~a | c)) + 1126891415,    10);
    c = a + LEFTROTATE(c + in[14] + (a ^ (~d | b)) - 1416354905,    15);
    b = d + LEFTROTATE(b + in[5]  + (d ^ (~c | a)) - 57434055,      21);
    a = b + LEFTROTATE(a + in[12] + (c ^ (~d | b)) + 1700485571,     6);
    d = a + LEFTROTATE(d + in[3]  + (b ^ (~a | c)) - 1894986606,    10);
    c = a + LEFTROTATE(c + in[10] + (a ^ (~d | b)) - 1051523,       15);
    b = d + LEFTROTATE(b + in[1]  + (d ^ (~c | a)) - 2054922799,    21);
    a = b + LEFTROTATE(a + in[8]  + (c ^ (~d | b)) + 1873313359,     6);
    d = a + LEFTROTATE(d + in[15] + (b ^ (~a | c)) - 30611744,      10);
    c = a + LEFTROTATE(c + in[6]  + (a ^ (~d | b)) - 1560198380,    15);
    b = d + LEFTROTATE(b + in[13] + (d ^ (~c | a)) + 1309151649,    21);
    a = b + LEFTROTATE(a + in[4]  + (c ^ (~d | b)) - 145523070,      6);
    d = a + LEFTROTATE(d + in[11] + (b ^ (~a | c)) - 1120210379,    10);
    c = a + LEFTROTATE(c + in[2]  + (a ^ (~d | b)) + 718787259,     15);
    b = d + LEFTROTATE(b + in[9]  + (d ^ (~c | a)) - 343485551,     21);

    // Update state
    buf[0] += a;
    buf[1] += b;
    buf[2] += c;
    buf[3] += d;
}