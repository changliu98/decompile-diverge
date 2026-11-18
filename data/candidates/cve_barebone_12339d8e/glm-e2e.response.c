int mobi_reconstruct_infl(char *output, void *indx, void *indx_entry) {
    char *word = *((char **)indx_entry); // -0x28(%rbp)
    size_t tag_count = 0; // -0x30(%rbp)
    size_t *tag_values = mobi_get_indxentry_tagarray(&tag_count, indx_entry, 0x2a); // -0x38(%rbp)
    
    if (tag_values == NULL || tag_count == 0) {
        return 0;
    }

    const char *str1 = "<inf>"; // 0x3004
    const char *str2 = "</inf>"; // 0x300f
    const char *str3 = "<i>%s</i>"; // 0x301b

    strcpy(output, str1);
    
    size_t initial_len = strlen(str1) + strlen(str2); // -0x458(%rbp)
    size_t current_len = initial_len; // -0x460(%rbp)
    
    size_t word_len = strlen(word); // -0x468(%rbp)
    if (word_len > 0x1f4) {
        return 3;
    }

    void *cncx = *((void **)((char *)indx + 0x40));
    if (cncx == NULL) {
        return 3;
    }

    for (size_t i = 0; i < tag_count; i++) { // i @ -0x470(%rbp)
        size_t entry_idx = tag_values[i]; // -0x478(%rbp)
        
        void *arr_base = *((void **)((char *)indx + 0x48));
        if (entry_idx >= *((size_t *)((char *)indx + 0x8))) {
            return 3;
        }

        size_t *tag_arr1 = mobi_get_indxentry_tagarray(&(size_t){0}, (char *)arr_base + entry_idx * 0x18, 0x5); // -0x488(%rbp)
        size_t *tag_arr2 = mobi_get_indxentry_tagarray(&(size_t){0}, (char *)arr_base + entry_idx * 0x18, 0x1a); // -0x498(%rbp)
        
        if (tag_arr1 != tag_arr2) {
            return 3;
        }

        for (size_t j = 0; j < tag_arr2[0]; j++) { // j @ -0x4a0(%rbp)
            char infl_str[0x1f4 + 1] = {0}; // -0x250(%rbp)
            char *cncx_str = mobi_get_cncx_string(cncx, tag_arr1[j]); // -0x4a8(%rbp)
            
            if (cncx_str == NULL) {
                return 7;
            }

            if (strlen(cncx_str) > 0) {
                snprintf(infl_str, 0x1f4, "<i>%s</i>", cncx_str);
            }
            free(cncx_str);

            char decoded[0x1f5] = {0}; // -0x6a0(%rbp)
            char *infl_ptr = *((char **)((char *)arr_base + entry_idx * 0x18)); // -0x6a8(%rbp)
            memcpy(decoded, word, word_len);
            
            size_t decoded_len = (unsigned int)word_len; // -0x6ac(%rbp)
            int ret = mobi_decode_infl(decoded, infl_ptr, &decoded_len); // -0x6b0(%rbp)
            if (ret != 0) {
                return ret;
            }

            if (decoded_len != 0) {
                char temp[0x1f4 + 1]; // -0x450(%rbp)
                int formatted_len = snprintf(temp, 0x1f4, str3, infl_str, decoded); // -0x6b4(%rbp)
                
                if (formatted_len <= 0x1f4) {
                    current_len += strlen(temp);
                    if (current_len > 0x61a8) {
                        return 1;
                    }
                    strcat(output, temp);
                }
            }
        }
    }

    if (current_len == initial_len) {
        output[0] = '\0';
    } else {
        strcat(output, str2);
    }

    return 0;
}