int
sec_hash(unsigned char *salted_hash,
                           unsigned int salted_hash_length,
                           unsigned char *data,
                           unsigned int data_length)
{
    int ret = -1;

    if (salted_hash_length == 20) {
        unsigned char salted_hash_check[20];
        SHA1_CTX ctx;
        SHA1_Init(&ctx);
        SHA1_Update(&ctx, salted_hash, 8);
        SHA1_Update(&ctx, data, data_length);
        SHA1_Update(&ctx, salted_hash, 8);
        SHA1_Final(salted_hash_check, &ctx);
        if (memcmp__bench(salted_hash_check, salted_hash, 20) == 0)
            ret = 0;
    } else if (salted_hash_length == 32) {
        unsigned char salted_hash_check[32];
        SHA256_CTX ctx;
        SHA256_Init(&ctx);
        SHA256_Update(&ctx, salted_hash, 8);
        SHA256_Update(&ctx, data, data_length);
        SHA256_Update(&ctx, salted_hash, 8);
        SHA256_Final(salted_hash_check, &ctx);
        if (memcmp__bench(salted_hash_check, salted_hash, 32) == 0)
            ret = 0;
    }

    return ret;
}