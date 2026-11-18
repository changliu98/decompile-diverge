static void encrypt(struct arc4context *parc4ctx, u8 *key, u32 keylen)
{
	u32	t, u;
	u32	keyindex;
	u32	stateindex;
	u8 *state;
	u32 x;

	state = parc4ctx->state;
	t = x = stateindex = keyindex = 0;

	
	while (stateindex < 256) {
		state[stateindex] = key[keyindex];
		keyindex++;
		stateindex++;
	}

	
	t = x = stateindex = keyindex = 0;
	while (stateindex < 256) {
		x = (key[keyindex] + state[x] + t) & 0xff;
		SwapBytes(state, x, stateindex);
		stateindex++;
		t = (t + 1) & 0xff;
		keyindex++;
	}

	
	parc4ctx->x = x;
	parc4ctx->y = x;
}