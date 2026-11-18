static unsigned int fec_buffer_rs_index(unsigned int block, unsigned int index) {
  unsigned int rs_index;
  rs_index = block << FEC_RS_BLOCK_SHIFT;
  rs_index += index;
  return rs_index;
}