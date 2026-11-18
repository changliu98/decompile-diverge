const char *bittok2str_internal(struct tok *token_list, const char *fallback, int bitfield, const char *sep) {
    int offset = 0;
    const char *current_sep = "";

    while (token_list != NULL && token_list->str != NULL) {
        int mask = token_list->mask;
        
        // Iterate through powers of 2 (1, 2, 4, 8, ...)
        for (int bit = 1; bit != 0; bit <<= 1) {
            if (mask == (bitfield & bit)) {
                offset += snprintf(bittok2str_internal_buf + offset, 
                                   256 - offset, 
                                   "%s%s", 
                                   current_sep, 
                                   token_list->str);
                current_sep = sep;
                break; // Implicitly handled by the assembly jumping out of the loop
            }
        }
        token_list = token_list->next;
    }

    if (offset == 0) {
        const char *fb = (fallback != NULL) ? fallback : "0";
        snprintf(bittok2str_internal_buf, 256, "%s", fb);
    }

    return bittok2str_internal_buf;
}