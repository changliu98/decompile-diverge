bool trylock(char *lock) {
    return __atomic_exchange_n(lock, 1, __ATOMIC_SEQ_CST) == 0;
}