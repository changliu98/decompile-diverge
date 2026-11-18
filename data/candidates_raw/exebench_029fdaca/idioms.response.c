static __inline__ void atomic_set(struct atomic_t *a, float v)
{
  a->value = v;
}