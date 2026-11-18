bool s390_cpumsf_reached_trailer(size_t entry_size, size_t current_position)
{
    // Check if the current position has reached or passed the trailer boundary.
    // S390_CPUMSF_PAGESZ is the page size.
    // (S390_CPUMSF_PAGESZ + -1) computes the page mask (aligns down to page boundary).
    // (pos & (long)(S390_CPUMSF_PAGESZ + -1)) gets the offset of pos within its page.
    // (long)S390_CPUMSF_PAGESZ + -4 is the maximum valid data size per page (page size minus 4 bytes for trailer/header overhead).
    // The expression calculates the remaining space in the current page before the trailer.
    // If entry_sz is less than or equal to this remaining space, it means we haven't reached the trailer yet.
    // The cast to uint converts the boolean result (0 or 1) to an unsigned integer.
    return (uint)(entry_size <= ((long)S390_CPUMSF_PAGESZ + -4) - (current_position & (long)(S390_CPUMSF_PAGESZ + -1)));
}