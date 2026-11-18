char *mdir_name(const char *path) {
    size_t length = dir_len(path);
    
    // Check if the path ends with a slash (i.e., dir_len returned 0 for a root path like "/")
    // If length is 0, we need to keep the slash, so add_slash is true.
    // Otherwise, add_slash is false.
    char add_slash = (length == 0);
    
    // Allocate memory for the directory name.
    // Size is length + 1 (for the null terminator) + 1 (if we need to add a slash).
    char *dir_name = (char *)malloc(length + 1 + add_slash);
    
    if (dir_name == NULL) {
        return NULL;
    }
    
    // Copy the original path into the newly allocated memory
    memcpy(dir_name, path, length);
    
    // If the original path was just a root slash, dir_len returned 0.
    // We need to manually add the slash back.
    if (add_slash) {
        dir_name[length] = '.';
        length++;
    }
    
    // Null-terminate the string
    dir_name[length] = '\0';
    
    return dir_name;
}