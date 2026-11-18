int fatfs_get_sfn_display_name(char *dst, const char *src) {
    int i = 0;
    char c;
    bool condition;

    do {
        c = *src;
        condition = (c != '\0') && (i <= 11);
    } while (condition);

    // The loop above is a placeholder to show the condition check.
    // The actual logic from the assembly translates to the loop below:
    
    i = 0;
    while (true) {
        c = *src;
        if (c == '\0' || i > 11) {
            break;
        }
        src++;
        
        if (c == ' ') {
            continue;
        }
        
        if (c >= 'A' && c <= 'Z') {
            c += 32; // Convert to lowercase
        }
        
        *dst = c;
        dst++;
        i++;
    }
    
    *dst = '\0';
    return 1;
}