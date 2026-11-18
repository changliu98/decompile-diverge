void basename_discriminant(char *filename, long *h, long *len)
{
    // Find the last occurrence of '/' (0x2f) in the filename
    char *basename_ptr = strrchr(filename, 0x2f);
    // If '/' is found, move pointer to the character after it (start of basename)
    if (basename_ptr != NULL) {
        basename_ptr++;
    } else {
        // If no '/' is found, the entire filename is the basename
        basename_ptr = filename;
    }
    // Initialize hash value and length to zero
    *len = 0;
    *h = 0;
    // Iterate through each character of the basename
    while (*basename_ptr != '\0') {
        // Compute hash using a simple polynomial rolling hash function
        *h = *h * 0x21 + (long)*basename_ptr;
        // Increment the length counter
        *len = *len + 1;
        // Move to the next character
        basename_ptr++;
    }
}