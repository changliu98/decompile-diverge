int __cdecl num_contig_ptes(unsigned __int64 size, size_t *pgsize)
{
    *pgsize = size;

    if (size == 0x80) {
        return 1;
    } else if (size == 0x81) {
        *pgsize = PAGE_SIZE;
        return CONT_PTES;
    } else if (size == 0x82) {
        *pgsize = 128;
        return CONT_PMDS;
    }

    return 0;
}