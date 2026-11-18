int ospf6_print_lshdr(netdissect_options *ndo, const uint8_t *ls_hdr, const uint8_t *data_end) {
    // The ndo structure has its length/offset at offset 0x0 and a print/format 
    // function pointer at offset 0x8.
    int (*ndo_printf)(netdissect_options *, const char *, ...) = *(int (**)(netdissect_options *, const char *, ...))((char*)ndo + 8);
    
    // 1. Bounds Check: Ensure the header fits within the packet bounds
    if (ls_hdr + 0x14 > data_end) {
        return 1;
    }
    
    // 2. Bounds Check: Ensure the header fits within the captured length (ndo->snapend or similar)
    if (ls_hdr + 0x2 > (const uint8_t *)*(int64_t *)ndo - 2) {
        return 1;
    }
    
    // 3. Bounds Check: Another length validation against the captured length
    if (ls_hdr + 0xc > (const uint8_t *)*(int64_t *)ndo - 4) {
        return 1;
    }
    
    // Extract fields from the LSA header
    const char *ls_id = ipaddr_string(ndo, ls_hdr + 8);
    uint32_t ls_seq = EXTRACT_32BITS(ls_hdr + 0xc);
    uint16_t ls_age = EXTRACT_16BITS(ls_hdr);
    uint16_t ls_checksum = EXTRACT_16BITS(ls_hdr + 0x12);
    
    // Print the LSA header information
    ndo_printf(ndo, "\n    Advertising Router %s, seq 0x%08x, age %us, length %u", 
               ls_id, ls_seq, ls_age, ls_checksum - 0x14);
               
    // Print the LSA type-specific information
    uint16_t ls_type = EXTRACT_16BITS(ls_hdr + 2);
    ospf6_print_ls_type(ndo, ls_type, ls_hdr + 4);
    
    return 0;
}