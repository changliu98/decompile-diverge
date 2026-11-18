unsigned int __cdecl fec_buffer_rs_index(unsigned int i, unsigned int j)
{
  return j + (i << DM_VERITY_FEC_BUF_RS_BITS);
}