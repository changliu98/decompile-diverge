void a_store(int *ptr, int value) {
    // Store the value x into the memory location pointed to by p
    *ptr = value;
    // Acquire a lock to ensure exclusive access
    LOCK();
    // Release the lock
    UNLOCK();
}