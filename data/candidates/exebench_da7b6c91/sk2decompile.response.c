static inline void avro_refcount_set(int *refcount, int value) {
  int new_refcount = value;
  *refcount = new_refcount;
}