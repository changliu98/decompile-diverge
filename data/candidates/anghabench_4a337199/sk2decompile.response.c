static inline unsigned REG_A6XX_SP_FS_MRT(unsigned idx) {
  unsigned regaddr;
  regaddr = (0x8200 + idx);
  regaddr += 0x1000;
  return regaddr;
}