void sha1_transform(void *ctx, unsigned char *data)
{
    struct sha1_context *c = (struct sha1_context *)ctx;
    unsigned int w[80];
    unsigned int a; unsigned int b; unsigned int c; unsigned int d; unsigned int e;
    unsigned int t;
    unsigned int i = 0;
    unsigned int j = 0;
    for (i = 0; i < 16; i++)
    {
        w[i] = (data[j] << 24) + (data[j + 1] << 16) + (data[j + 2] << 8) + (data[j + 3]);
        j += 4;
    }
    for ( ; i < 80; i++)
    {
        w[i] = w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16];
        w[i] = (w[i] << 1) | (w[i] >> (32 - 1));
    }
    a = c->state[0];
    b = c->state[1];
    c = c->state[2];
    d = c->state[3];
    e = c->state[4];
    for (i = 0; i < 20; i++)
    {
        t = a + ((b & c) | (~b & d)) + c->k[0] + w[i];
        e = d;
        d = c;
        c = (b << 30) | (b >> (32 - 30));
        b = a;
        a = t;
    }
    for ( ; i < 40; i++)
    {
        t = a + (b ^ c ^ d) + c->k[1] + w[i];
        e = d;
        d = c;
        c = (b << 30) | (b >> (32 - 30));
        b = a;
        a = t;
    }
    for ( ; i < 60; i++)
    {
        t = a + ((b & c) | (b & d) | (c & d)) + c->k[2] + w[i];
        e = d;
        d = c;
        c = (b << 30) | (b >> (32 - 30));
        b = a;
        a = t;
    }
    for ( ; i < 80; i++)
    {
        t = a + (b ^ c ^ d) + c->k[3] + w[i];
        e = d;
        d = c;
        c = (b << 30) | (b >> (32 - 30));
        b = a;
        a = t;
    }
    c->state[0] += a;
    c->state[1] += b;
    c->state[2] += c;
    c->state[3] += d;
    c->state[4] += e;
}