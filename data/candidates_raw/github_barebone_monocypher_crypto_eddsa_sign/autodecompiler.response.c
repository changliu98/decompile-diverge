void crypto_eddsa_sign(u8 signature[64],
                       const u8 secret_key[32],
                       const u8 *message, size_t len)
{

    u8 az[64];
    crypto_blake2b(az, 64, secret_key, 32);
    crypto_eddsa_trim_scalar(az, az);


    u8 R[32];
    u8 r[32];
    hash_reduce(R, az + 32, 32, message, len, 0);
    crypto_eddsa_scalarbase(R, r);


    u8 h_ram[32];
    hash_reduce(h_ram, R, 32, secret_key + 32, 32, message, len);
    for (size_t i = (0); i < (32); i++) (signature)[i] = (R)[i];


    crypto_eddsa_mul_add(signature + 32, h_ram, az, r);
    crypto_wipe(az , sizeof(az));
    crypto_wipe(r , sizeof(r));
}