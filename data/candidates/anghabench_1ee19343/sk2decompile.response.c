static inline bool is_ioat_suspended(unsigned long status) {
  if ((status & IOAT_STATUS_MASK) == IOAT_STATUS_SUSPENDED)
    return true;
  else
    return false;
}