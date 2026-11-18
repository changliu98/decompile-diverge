static inline unsigned int dm_verity_fec_buf_rs_idx(unsigned int i, unsigned int j)
{
 return (i << DM_VERITY_FEC_BUF_RS_BITS) + j;
}