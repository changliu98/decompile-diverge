static inline void StoreUintptr(volatile unsigned long long *destPtr,
                                unsigned long long value) {
  unsigned long long oldValue;
  oldValue = *destPtr;
  while (oldValue !=
         __sync_val_compare_and_swap((volatile unsigned long long *)destPtr,
                                     value, oldValue)) {
    oldValue = *destPtr;
  }
}