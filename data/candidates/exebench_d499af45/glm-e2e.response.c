void validate_rt_entry(unsigned long long *entry) {
    *entry &= 0xFFFFFFFFFFFFFFDFULL; // Clear bit 5
    *entry &= 0xFFFFFFFFFFFFFF3FULL; // Clear bits 5 and 6
    *entry |= 0x0ULL;                // No-op (OR with 0)
    *entry |= 0x3ULL;                // Set bits 0 and 1
}