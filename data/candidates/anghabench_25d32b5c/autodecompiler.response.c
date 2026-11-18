__attribute__((used)) static unsigned int fec_buffer_rs_index(unsigned int block, unsigned int parity)
{
	return (block << DM_VERITY_FEC_BUF_RS_BITS) + parity;
}