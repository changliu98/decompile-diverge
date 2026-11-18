static inline char *emit_literal(char *op,
				 const char *literal,
				 int len, bool allow_fast_path)
{
	int n = len - 1;	/* Zero-length literals are disallowed */

	if (n < 60) {
		/* Fits in tag byte */
		*op++ = LITERAL | (n << 2);

/*
 * The vast majority of copies are below 16 bytes, for which a
 * call to memcpy is overkill. This fast path can sometimes
 * copy up to 15 bytes too much, but that is okay in the
 * main loop, since we have a bit to go on for both sides:
 *
 *   - The input will always have kInputMarginBytes = 15 extra
 *     available bytes, as long as we're in the main loop, and
 *     if not, allow_fast_path = false.
 *   - The output will always have 32 spare bytes (see
 *     MaxCompressedLength).
 */
		if (allow_fast_path && len <= 16) {
			unaligned_copy64(literal, op);
			unaligned_copy64(literal + 8, op + 8);
			return op + len;
		}
	} else {
		/* Encode in upcoming bytes */
		char *base = op;
		int count = 0;
		op++;
		while (n > 0) {
			*op++ = n & 0xff;
			n >>= 8;
			count++;
		}
		DCHECK(count >= 1);
		DCHECK(count <= 4);
		*base = LITERAL | ((59 + count) << 2);
	}
	memcpy(op, literal, len);
	return op + len;
}