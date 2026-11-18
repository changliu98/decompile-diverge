static void validate_st_entry(unsigned long *st_entry) {
  *st_entry &= ~(1UL << 5);
  *st_entry &= ~(1UL << 63);
}