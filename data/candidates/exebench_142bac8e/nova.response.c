static inline void wordstore(char s[2], u32 v)
{
	s[0] = v & 0xff;
	s[1] = (v >> 8) & 0xff;
}