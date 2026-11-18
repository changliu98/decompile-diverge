int _safe_calloc_check_add(uint64_t arg1, uint64_t arg2, uint64_t *arg3) {
    uint64_t local1 = arg1;
    uint64_t local2 = arg2;
    uint64_t local3;
    
    if (arg3 != NULL) {
        local3 = (uint64_t)arg3;
    } else {
        local3 = (uint64_t)&local3;
    }
    
    uint64_t sum = local1 + local2;
    int carry = __builtin_uaddll_overflow(local1, local2, (unsigned long long *)local3);
    
    return !carry;
}