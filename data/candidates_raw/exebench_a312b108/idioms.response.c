static inline void *swap(void *var, void *val)
{
  void *ret = var;
  var = val;
  return ret;
}