char *func0(const char *arg) {
    size_t len = strlen(arg);
    size_t out_idx = 0;
    char *out = malloc(len * 2);
    
    for (size_t i = 0; i < len; i++) {
        if (i > 0 && isalpha((unsigned char)arg[i])) {
            if (isupper((unsigned char)arg[i - 1]) || isdigit((unsigned char)arg[i - 1])) {
                out[out_idx++] = '_';
                out[out_idx++] = tolower((unsigned char)arg[i]);
                continue;
            }
        }
        
        if (i > 0 && isalpha((unsigned char)arg[i]) && isalpha((unsigned char)arg[i - 1]) && isupper((unsigned char)arg[i + 1])) {
            out[out_idx++] = '_';
            out[out_idx++] = tolower((unsigned char)arg[i]);
            continue;
        }
        
        out[out_idx++] = tolower((unsigned char)arg[i]);
    }
    
    out[out_idx] = '\0';
    return out;
}