int twofish_keysize(int *keysize) {
    // Argument check: ensure the pointer is not NULL
    crypt_argchk("twofish_keysize.c", "keysize", 695);
    
    if (*keysize < 16) {
        return 3; // CRYPT_INVALID_KEYSIZE
    } else if (*keysize < 24) {
        *keysize = 16;
        return 0; // CRYPT_OK
    } else if (*keysize < 32) {
        *keysize = 24;
        return 0; // CRYPT_OK
    } else {
        *keysize = 32;
        return 0; // CRYPT_OK
    }
}