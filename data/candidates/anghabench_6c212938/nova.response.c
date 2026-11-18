static inline void copy_le16(char s[2], unsigned int x) {
	s[0] = (x >> 8) & 0xff;
	s[1] = x & 0xff;
}