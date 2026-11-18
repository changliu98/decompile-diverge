uint fec_buffer_rs_index(uint i,uint j)

{
  uint j_local;
  uint i_local;
  
  return (i << ((byte)DM_VERITY_FEC_BUF_RS_BITS & 0x1f)) + j;
}