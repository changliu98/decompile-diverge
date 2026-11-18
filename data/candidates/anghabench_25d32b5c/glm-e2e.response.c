int fec_buffer_rs_index(int edi, int esi) {
    return (edi << DM_VERITY_FEC_BUF_RS_BITS) + esi;
}