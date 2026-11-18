void spin_unlock(char *lock) {
    *lock = 0;
}