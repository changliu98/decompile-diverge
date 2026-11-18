// Determines the number of contiguous page table entries (PTEs) required for a given size.
// Parameters:
//   size: An identifier indicating the type of memory mapping or size configuration.
//   pgsize: Output parameter to store the calculated page size.
// Returns:
//   The number of contiguous PTEs, or 0 if the size is not recognized.
int num_contig_ptes(unsigned_long mapping_type, size_t *output_page_size)
{
    // Initialize the output page size with the input size.
    *output_page_size = mapping_type;
    
    // If size is 0x80, return 1 contiguous PTE.
    if (mapping_type == 0x80) {
        return 1;
    } 
    // If size is 0x81, set page size to PAGE_SIZE and return CONT_PTES.
    else if (mapping_type == 0x81) {
        *output_page_size = PAGE_SIZE;
        return CONT_PTES;
    } 
    // If size is 0x82, set page size to 0x80 and return CONT_PMDS.
    else if (mapping_type == 0x82) {
        *output_page_size = 0x80;
        return CONT_PMDS;
    }
    
    // Return 0 if the size is not recognized.
    return 0;
}