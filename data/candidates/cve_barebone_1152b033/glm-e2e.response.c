int hci_req_sync(void *arg1, void *arg2, void *arg3, int arg4, void *arg5) {
    int ret;

    // Check if the bit is set. If not, return -100 (0xffffff9c)
    if (!test_bit(0, arg1)) {
        return -100;
    }

    // Lock the mutex located at offset 0x8 from arg1
    mutex_lock(arg1 + 0x8);

    // Call the internal sync function and store the result
    ret = __hci_req_sync(arg1, arg2, arg3, arg4, arg5);

    // Unlock the mutex
    mutex_unlock(arg1 + 0x8);

    return ret;
}