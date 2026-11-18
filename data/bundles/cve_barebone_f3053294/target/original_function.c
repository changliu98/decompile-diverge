static char *
utf_16le_to_utf_8_truncated(const wchar_t *utf_16, char *utf_8,
    size_t utf_8_len)
{
	wchar_t c, c2;
	uint32_t uc;

	if (utf_8_len == 0) {
		/*
		 * Not even enough room for a trailing '\0'.
		 * Don't put anything into the buffer.
		 */
		return (utf_8);
	}

	while ((c = *utf_16++) != '\0') {
		if (IS_LEADING_SURROGATE(c)) {
			/*
			 * Leading surrogate.  Must be followed by
			 * a trailing surrogate.
			 */
			c2 = *utf_16;
			if (c2 == '\0') {
				/*
				 * Oops, string ends with a lead
				 * surrogate.  Try to drop in
				 * a REPLACEMENT CHARACTER, and
				 * don't move the string pointer,
				 * so on the next trip through
				 * the loop we grab the terminating
				 * '\0' and quit.
				 */
				uc = REPLACEMENT_CHARACTER;
			} else {
				/*
				 * OK, we can consume this 2-octet
				 * value.
				 */
				utf_16++;
				if (IS_TRAILING_SURROGATE(c2)) {
					/*
					 * Trailing surrogate.
					 * This calculation will,
					 * for c being a leading
					 * surrogate and c2 being
					 * a trailing surrogate,
					 * produce a value between
					 * 0x100000 and 0x10ffff,
					 * so it's always going to be
					 * a valid Unicode code point.
					 */
					uc = SURROGATE_VALUE(c, c2);
				} else {
					/*
					 * Not a trailing surrogate;
					 * try to drop in a
					 * REPLACEMENT CHARACTER.
					 */
					uc = REPLACEMENT_CHARACTER;
				}
			}
		} else {
			/*
			 * Not a leading surrogate.
			 */
			if (IS_TRAILING_SURROGATE(c)) {
				/*
				 * Trailing surrogate without
				 * a preceding leading surrogate.
				 * Try to drop in a REPLACEMENT
				 * CHARACTER.
				 */
				uc = REPLACEMENT_CHARACTER;
			} else {
				/*
				 * This is a valid BMP character;
				 * drop it in.
				 */
				uc = c;
			}
		}

		/*
		 * OK, uc is a valid Unicode character; how
		 * many bytes worth of UTF-8 does it require?
		 */
		if (uc < 0x0080) {
			/* 1 byte. */
			if (utf_8_len < 2) {
				/*
				 * Not enough room for that byte
				 * plus a trailing '\0'.
				 */
				break;
			}
			*utf_8++ = (char)uc;
			utf_8_len--;
		} else if (uc < 0x0800) {
			/* 2 bytes. */
			if (utf_8_len < 3) {
				/*
				 * Not enough room for those bytes
				 * plus a trailing '\0'.
				 */
				break;
			}
			*utf_8++ = ((uc >> 6) & 0x3F) | 0xC0;
			*utf_8++ = ((uc >> 0) & 0x3F) | 0x80;
			utf_8_len -= 2;
		} else if (uc < 0x010000) {
			/* 3 bytes. */
			if (utf_8_len < 4) {
				/*
				 * Not enough room for those bytes
				 * plus a trailing '\0'.
				 */
				break;
			}
			*utf_8++ = ((uc >> 12) & 0x0F) | 0xE0;
			*utf_8++ = ((uc >> 6) & 0x3F) | 0x80;
			*utf_8++ = ((uc >> 0) & 0x3F) | 0x80;
			utf_8_len -= 3;
		} else {
			/* 4 bytes. */
			if (utf_8_len < 5) {
				/*
				 * Not enough room for those bytes
				 * plus a trailing '\0'.
				 */
				break;
			}
			*utf_8++ = ((uc >> 18) & 0x03) | 0xF0;
			*utf_8++ = ((uc >> 12) & 0x3F) | 0x80;
			*utf_8++ = ((uc >> 6) & 0x3F) | 0x80;
			*utf_8++ = ((uc >> 0) & 0x3F) | 0x80;
			utf_8_len -= 3;
		}
	}

	/*
	 * OK, we have enough room for (at least) a trailing '\0'.
	 * (We started out with enough room, thanks to the test
	 * for a zero-length buffer at the beginning, and if
	 * there wasn't enough room for any character we wanted
	 * to put into the buffer *plus* a trailing '\0',
	 * we'd have quit before putting it into the buffer,
	 * and thus would have left enough room for the trailing
	 * '\0'.)
	 *
	 * Drop it in.
	 */
	*utf_8 = '\0';

	/*
	 * Return a pointer to the terminating '\0', in case we
	 * want to drop something in after that.
	 */
	return (utf_8);
}