void vector64_dst_append(void *sb, void **handle_ptr, void *vec, int reg_index, int width) {
    // The vector structure has an array of 12-byte structs at offset 0xf4
    // Each struct contains an int (size) and an int (reg_id)
    uint8_t *vec_base = (uint8_t *)vec;
    int *reg_info = (int *)(vec_base + 0xf4 + reg_index * 12);
    
    int size = reg_info[0];
    int reg_id = reg_info[1];
    
    if (size != -1) {
        width = size;
    }
    
    if (width != 0 && width != -1) {
        int vec_size = vector_size(vec);
        int total_width = width * vec_size;
        const char *fmt_str = "%s, ";
        uint64_t rem = (vec_size > 0) ? ((uint64_t)(vec_size - 1) % 64) : 0;
        uint64_t idx = (rem < 64) ? rem : 0;
        uint64_t mask = bitmask_by_width[idx];
        
        if (total_width >= 64) {
            total_width -= 64;
            fmt_str = "%s";
        }
        
        if (total_width > 0 && total_width < 64) {
            const char *reg_name1 = r_str_getf(cs_reg_name(*handle_ptr, reg_id));
            uint64_t mask2 = bitmask_by_width_1f8 ^ (bitmask_by_width[vec_size - 1] << total_width);
            const char *reg_name2 = r_str_getf(cs_reg_name(*handle_ptr, reg_id));
            
            r_strbuf_appendf(sb, "%s = %s & 0x%" PRIx64 " | (%s & 0x%" PRIx64 ") %s",
                             sb, total_width, mask, reg_name1, mask2, reg_name2, fmt_str);
        } else {
            int rem2 = vec_size % 64;
            const char *reg_name1 = r_str_getf(cs_reg_name(*handle_ptr, reg_id));
            uint64_t mask2 = bitmask_by_width_1f8 ^ (bitmask_by_width[rem2 - 1] << total_width);
            const char *reg_name2 = r_str_getf(cs_reg_name(*handle_ptr, reg_id));
            
            r_strbuf_appendf(sb, "%s = %s & 0x%" PRIx64 " | (%s & 0x%" PRIx64 ") %s",
                             sb, mask, reg_name1, mask2, reg_name2, fmt_str);
        }
    } else {
        const char *reg_name = r_str_getf(cs_reg_name(*handle_ptr, reg_id));
        r_strbuf_appendf(sb, "%s%s", sb, reg_name);
    }
}