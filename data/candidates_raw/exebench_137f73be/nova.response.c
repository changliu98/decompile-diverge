static int func0(struct dib0090_state *state, u8 r, u8 reg, u8 * b, u8 len)
{
	u8 b0[] = {reg};
	int ret;

	if (mutex_lock_interruptible(state->i2c_buffer_lock) < 0) {
		ret = 3;
		goto ret;
	}

	if (write_i2c(state->i2c_buffer_lock, b0, r, 1)!= 1) {
		ret = 3;
		goto ret;
	}

	if (read_i2c(state->i2c_buffer_lock, b, len)!= len) {
		ret = 3;
		goto ret;
	}

	ret = 0;
 ret:
	mutex_unlock(state->i2c_buffer_lock);
	return ret;
}