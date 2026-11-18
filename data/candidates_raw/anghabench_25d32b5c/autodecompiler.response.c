__attribute__((used)) static unsigned int array_index(unsigned int block, unsigned int parity)
{
	return (block << DM_VERITY_FEC_BUF_RS_BITS) + parity;
}