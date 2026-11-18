void sha1_update(SHA1_CTX *ctx, const BYTE *data, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        // Buffer the incoming data byte by byte
        ctx->data[ctx->datalen++] = data[i];

        // When the internal buffer reaches 64 bytes (512 bits), process it
        if (ctx->datalen == 64)
        {
            sha1_transform(ctx, ctx->data);
            ctx->bitlen += 512;
            ctx->datalen = 0;
        }
    }
}