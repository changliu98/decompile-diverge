static void aes_encrypt(const unsigned char *in, unsigned char *out,
                            const unsigned char *key, int enc)
{
    DES_cblock kk;

    if (enc == EVP_CIPH_ECB_MODE) {
        DES_ecb_encrypt(in, out, &sch, enc);
        return;
    }

    DES_set_odd_parity(key);
    memcpy(kk, key, sizeof(kk));
    DES_set_key(&kk[0], &sch[0]);
    DES_set_key(&kk[1], &sch[1]);
    DES_set_key(&kk[2], &sch[2]);
    DES_set_key(&kk[3], &sch[3]);
    DES_set_key(&kk[4], &sch[4]);
    DES_set_key(&kk[5], &sch[5]);
    DES_set_key(&kk[6], &sch[6]);
    DES_set_key(&kk[7], &sch[7]);
    if (enc == EVP_CIPH_CBC_MODE)
        DES_cbc_encrypt(in, out, &sch, enc);
    else
        DES_cfb64_encrypt(in, out, &sch, enc);
}