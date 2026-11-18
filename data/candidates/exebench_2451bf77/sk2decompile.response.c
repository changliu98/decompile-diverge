static inline void spin_unlock(spinlock_t *lock) {
  {
# 102 "/usr/local/ddv/models/con2/src/linux/spinlock.h"
    *(lock) = 0;
# 103 "/usr/local/ddv/models/con2/src/linux/spinlock.h"
    return;
  }
}