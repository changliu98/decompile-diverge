static inline unsigned int fec_buffer_rs_index(unsigned int i, unsigned int j)
{
 return (i << DM_VERITY_FEC_BUF_RS_BITS) + j;
}