static inline void spin_unlock(int *lock)
{
    *lock = 0;
}