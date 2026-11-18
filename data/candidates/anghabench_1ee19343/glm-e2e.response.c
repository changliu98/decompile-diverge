bool is_ioat_suspended(unsigned long long state) {
    return (state & IOAT_CHANSTS_STATUS) == IOAT_CHANSTS_SUSPENDED;
}