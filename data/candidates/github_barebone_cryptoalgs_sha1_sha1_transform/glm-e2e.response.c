void sha1_transform(struct sha1_ctx *ctx, const uint8_t *data) {
    uint32_t w[80];
    uint32_t a, b, c, d, e, f, tmp;
    int i;

    // 1. Initialize the first 16 words in the arrays w[0..15]
    for (i = 0; i < 16; i++) {
        w[i] = (data[i * 4] << 24) |
               (data[i * 4 + 1] << 16) |
               (data[i * 4 + 2] << 8) |
               (data[i * 4 + 3]);
    }

    // 2. Extend the first 16 words into the remaining 64 words w[16..79]
    for (i = 16; i < 80; i++) {
        w[i] = (w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16]);
        w[i] = (w[i] << 1) | (w[i] >> 31); // Rotate left by 1
    }

    // 3. Initialize hash value for this chunk
    a = ctx->state[0];
    b = ctx->state[1];
    c = ctx->state[2];
    d = ctx->state[3];
    e = ctx->state[4];

    // 4. Main loop
    for (i = 0; i < 80; i++) {
        if (i < 20) {
            f = (b & c) | ((~b) & d);
            tmp = ctx->k[0];
        } else if (i < 40) {
            f = b ^ c ^ d;
            tmp = ctx->k[1];
        } else if (i < 60) {
            f = (b & c) | (b & d) | (c & d);
            tmp = ctx->k[2];
        } else {
            f = b ^ c ^ d;
            tmp = ctx->k[3];
        }

        // Rotate left by 5
        tmp += (a << 5) | (a >> 27);
        tmp += e;
        tmp += f;
        tmp += w[i];

        e = d;
        d = c;
        // Rotate left by 30
        c = (b << 30) | (b >> 2);
        b = a;
        a = tmp;
    }

    // 5. Add this chunk's hash to result so far
    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
}