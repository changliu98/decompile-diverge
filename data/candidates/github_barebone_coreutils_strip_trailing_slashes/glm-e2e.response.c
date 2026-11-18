bool strip_trailing_slashes(char *path) {
    char *base = last_component(path);
    
    // If the last component is an empty string, fall back to the original path
    if (base[0] == '\0') {
        base = path;
    }
    
    // Calculate the end of the base name
    char *end = base + base_len(base);
    
    // Check if there are trailing slashes to strip
    bool had_slash = (*end != '\0');
    
    // Strip the trailing slashes by null-terminating
    *end = '\0';
    
    return had_slash;
}