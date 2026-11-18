void toup(char *char_ptr)
{
    // Check if the character is a lowercase letter (ASCII range 'a' to 'z')
    // '`' is 0x60 and '{' is 0x7B; characters between them are 'a'-'z'
    if (*char_ptr > '`' && *char_ptr < '{') {
        // Convert lowercase to uppercase by subtracting 0x20 (32)
        *char_ptr -= 0x20;
    }
}