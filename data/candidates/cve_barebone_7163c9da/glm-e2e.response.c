struct node *parse_string_node(const char **data, long length) {
    struct plist_data *plist = plist_new_plist_data();
    plist->type = 3;
    
    // The `shl $0x0` is a no-op, likely a compiler artifact or alignment instruction.
    // It effectively allocates `length + 1` bytes for the string and null terminator.
    plist->str = malloc(length + 1);
    
    memcpy(plist->str, *data, length);
    
    // Null-terminate the string
    ((char *)plist->str)[length] = '\0';
    
    // Calculate and store the string length
    plist->length = strlen(plist->str);
    
    // node_create takes the type (0) and the plist_data struct
    return node_create(0, plist);
}