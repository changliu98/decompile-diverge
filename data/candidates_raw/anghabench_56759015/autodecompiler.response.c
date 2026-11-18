__attribute__((used)) static inline int M_Offset_PseudoRandom(int channel)
{
	return 0x70 + (2 * (channel & 1));
}