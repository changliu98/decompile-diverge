void validate_st_entry(uint64_t *entry) {
    *entry &= 0xFFFFFFFFFFFFFFDF; // Clear the 6th bit (bit index 5)
    *entry |= 0x0;                // No-op: OR with 0 changes nothing
}