int FABSQ(PROV_CIPHER_CTX *dst, const PROV_CIPHER_CTX *src)
{
    dst->flags = src->flags & 0x7FFFFFFFFFFFFFFFULL;
    dst->engine = src->engine;
    return 1;
}