unsigned fec_buffer_rs_index(unsigned i, unsigned j)
{
	return (i << DM_VERITY_FEC_BUF_RS_BITS) + j;
}