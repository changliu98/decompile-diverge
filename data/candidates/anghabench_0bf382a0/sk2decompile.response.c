static inline unsigned REG_A5XX_VFD_DECODE_INSTR(unsigned vfd_id) {
  unsigned reg_val = 0;
  reg_val = reg_val | (0x00 << 16);
  reg_val = reg_val | (0x02 << 12);
  reg_val = reg_val | (0x02 << 8);
  reg_val = reg_val | (0x02 << 4);
  reg_val = reg_val | (vfd_id << 1);
  return reg_val;
}