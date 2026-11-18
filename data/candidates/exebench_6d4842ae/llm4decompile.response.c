void load_and_store(volatile int64_t *mem, int64_t value) {
  *mem = *mem + value;
}