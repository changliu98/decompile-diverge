static inline void dwordstore(char s, u32 v)
{
	s[0] = (v >> 0) & 0xff;
	s[1] = (v >> 8) & 0xff;
	s[2] = (v >> 16) & 0xff;
	s[3] = (v >> 24) & 0xff;
}