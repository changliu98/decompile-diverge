void handle_mlppp(struct ndo_handle *ndo, const uint8_t *p, int length) {
    // If the first integer in the struct is 0, call the function pointer with a specific format string
    if (*(int *)ndo == 0) {
        ((void (*)(struct ndo_handle *, const char *, ...))((void **)ndo)[1])(ndo, "%s");
    }

    // Store the function pointer from the struct
    void (*func_ptr)(struct ndo_handle *, const char *, ...) = ((void **)ndo)[1];
    
    // Store the struct pointer (likely for later use or debugging)
    struct ndo_handle *ndo_ptr = ndo;

    // Extract the 16-bit value and mask it with 0xFFF
    int val = EXTRACT_16BITS(p) & 0x0FFF;

    // Extract the first byte, mask the top 2 bits, and convert to string
    const char *flags_str = bittok2str(ppp_ml_flag_values, "#0x%x", *p & 0xC0);

    // Call the function pointer with all the extracted arguments
    func_ptr(ndo, "MLPPP, length %u, flags %s, seq 0x%03x, val 0x%04x", length, flags_str, val, val);
}