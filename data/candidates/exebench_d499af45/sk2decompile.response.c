static void validate_rt_entry(unsigned long *entry) {
  *entry &= ~(1UL << 5);
  *entry &= ~(1UL << 63);
  *entry &= ~(1UL << 0);
  *entry |= (1UL << 1);
}