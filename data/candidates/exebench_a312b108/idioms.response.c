static inline void *atomic_fetch_xor(void *var, void *val)
{
  void *ret = var;
  var = val;
  return ret;
}