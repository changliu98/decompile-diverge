int aes_decrypt_cbc(const unsigned char *in, size_t in_len,
                    unsigned char *out, const unsigned char *key,
                    int keysize, const unsigned char *iv)
{
    int blocks, idx;
    unsigned char iv_buf[16];
    unsigned char buf_in[16];
    unsigned char buf_out[16];

    if (in_len % 16 != 0)
        return 0;

    blocks = in_len / 16;

    for (idx = 0; idx < 16; idx++)
        iv_buf[idx] = iv[idx];

    for (idx = 0; idx < blocks; idx++) {
        int i;

        for (i = 0; i < 16; i++)
            buf_in[i] = in[idx * 16 + i];

        aes_decrypt(buf_in, buf_out, key, keysize);
        xor_buf(iv_buf, buf_out, 16);

        for (i = 0; i < 16; i++) {
            out[idx * 16 + i] = buf_out[i];
            iv_buf[i] = buf_in[i];
        }
    }

    return 1;
}