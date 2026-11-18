char *base_name(char *path) {
    char *comp;
    size_t len;
    int prefix_len;
    char *name;

    comp = last_component(path);
    
    if (*comp == '\0') {
        // The path ends with a slash (or is empty)
        comp = path;
        len = base_len(comp);
        prefix_len = 0;
    } else {
        len = base_len(comp);
        // If the character right after the base length is a slash, add 1 to length
        if (comp[len] == '/') {
            len += 1;
        }
        prefix_len = 0;
    }

    // Allocate space for the string, prefix, and null terminator
    name = (char *)ximalloc(len + prefix_len + 1);
    
    // If there's a prefix, prepend "./"
    if (prefix_len != 0) {
        name[0] = '.';
        name[1] = '/';
    }
    
    // Copy the component into the newly allocated string
    memcpy(name + prefix_len, comp, len);
    
    // Null-terminate the string
    name[prefix_len + len] = '\0';
    
    return name;
}