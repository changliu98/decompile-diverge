static void aes_decrypt(const unsigned char *in, unsigned char *out,
                             const unsigned char *key, int enc)
{
    unsigned char k1[4], k2[4], k3[4], k4[4];

    k1[0] = in[0];
    k1[1] = in[1];
    k1[2] = in[2];
    k1[3] = in[3];

    k2[0] = in[4];
    k2[1] = in[5];
    k2[2] = in[6];
    k2[3] = in[7];

    k3[0] = in[8];
    k3[1] = in[9];
    k3[2] = in[10];
    k3[3] = in[11];

    k4[0] = in[12];
    k4[1] = in[13];
    k4[2] = in[14];
    k4[3] = in[15];

    if (enc > 128) {
        rijndael_encrypt(k1, key + 224, k1);
        rijndael_encrypt(k2, key + 208, k2);
        rijndael_encrypt(k3, key + 192, k3);
        rijndael_encrypt(k4, key + 176, k4);
    } else {
        rijndael_decrypt(k1, key + 224, k1);
        rijndael_decrypt(k2, key + 208, k2);
        rijndael_decrypt(k3, key + 192, k3);
        rijndael_decrypt(k4, key + 176, k4);
    }

    out[0] = k1[0];
    out[1] = k1[1];
    out[2] = k1[2];
    out[3] = k1[3];

    out[4] = k2[0