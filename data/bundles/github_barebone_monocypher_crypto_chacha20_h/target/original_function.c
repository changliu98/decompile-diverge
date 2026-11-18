void crypto_chacha20_h(u8 out[32], const u8 key[32], const u8 in [16])
{
	u32 block[16];
	load32_le_buf(block     , chacha20_constant, 4);
	load32_le_buf(block +  4, key              , 8);
	load32_le_buf(block + 12, in               , 4);

	chacha20_rounds(block, block);

	// prevent reversal of the rounds by revealing only half of the buffer.
	store32_le_buf(out   , block   , 4); // constant
	store32_le_buf(out+16, block+12, 4); // counter and nonce
	WIPE_BUFFER(block);
}