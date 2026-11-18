bool __cdecl s390_cpumsf_reached_trailer(size_t entry_sz, size_t pos)
{
    // Calculate the offset of 'pos' from the start of its current page.
    // (Assuming S390_CPUMSF_PAGESZ is a power of 2, this acts as pos % PAGE_SIZE)
    size_t offset_in_page = (S390_CPUMSF_PAGESZ - 1) & pos;

    // Calculate the remaining space in the page before the 4-byte trailer.
    size_t remaining_space = S390_CPUMSF_PAGESZ - 4 - offset_in_page;

    // Return true if there is NOT enough space to fit another entry.
    // (i.e., the current position has reached or crossed into the trailer)
    return remaining_space < entry_sz;
}