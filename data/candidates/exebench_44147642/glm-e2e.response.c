void uppercase(int *c) {
    if ((*c >= 'a' && *c <= 'i') || 
        (*c >= 'j' && *c <= 'r') || 
        (*c >= 's' && *c <= 'z')) {
        *c = *c + 'A' - 'a';
    }
}