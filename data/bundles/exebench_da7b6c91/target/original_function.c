static inline void
avro_refcount_set(volatile int *refcount, int value)
{
 *refcount = value;
}