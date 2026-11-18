static unsigned int create_ce_flags(unsigned int flags) {
  unsigned int ce_flags;
  ce_flags = flags << CE_FLAGS_SHIFT;
  return ce_flags;
}