void md5_update(struct MD5state_st *c, void *data_, unsigned long len)
{
    unsigned char *data = data_;
    unsigned long i;
    for (i = 0; i < len; i++) {
        c->data[c->datalen] = data[i];
        c->datalen++;
        if (c->datalen == 64) {
            md5_transform (c, c->data);
            c->bitlen += 64 * 8;
            c->datalen = 0;
        }
    }
}