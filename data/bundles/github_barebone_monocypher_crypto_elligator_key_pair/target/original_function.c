void crypto_elligator_key_pair(u8 hidden[32], u8 secret_key[32], u8 seed[32])
{
	u8 pk [32]; // public key
	u8 buf[64]; // seed + representative
	COPY(buf + 32, seed, 32);
	do {
		crypto_chacha20_djb(buf, 0, 64, buf+32, zero, 0);
		crypto_x25519_dirty_fast(pk, buf); // or the "small" version
	} while(crypto_elligator_rev(buf+32, pk, buf[32]));
	// Note that the return value of crypto_elligator_rev() is
	// independent from its tweak parameter.
	// Therefore, buf[32] is not actually reused.  Either we loop one
	// more time and buf[32] is used for the new seed, or we succeeded,
	// and buf[32] becomes the tweak parameter.

	crypto_wipe(seed, 32);
	COPY(hidden    , buf + 32, 32);
	COPY(secret_key, buf     , 32);
	WIPE_BUFFER(buf);
	WIPE_BUFFER(pk);
}