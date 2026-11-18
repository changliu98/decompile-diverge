void crypto_eddsa_sign(u8 signature [64], const u8 secret_key[64],
                       const u8 *message, size_t message_size)
{
	u8 a[64];  // secret scalar and prefix
	u8 r[32];  // secret deterministic "random" nonce
	u8 h[32];  // publically verifiable hash of the message (not wiped)
	u8 R[32];  // first half of the signature (allows overlapping inputs)

	crypto_blake2b(a, 64, secret_key, 32);
	crypto_eddsa_trim_scalar(a, a);
	hash_reduce(r, a + 32, 32, message, message_size, 0, 0);
	crypto_eddsa_scalarbase(R, r);
	hash_reduce(h, R, 32, secret_key + 32, 32, message, message_size);
	COPY(signature, R, 32);
	crypto_eddsa_mul_add(signature + 32, h, a, r);

	WIPE_BUFFER(a);
	WIPE_BUFFER(r);
}