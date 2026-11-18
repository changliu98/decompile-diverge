int __cdecl affs_intl_toupper(int ch)
{
    // Check if the character is NOT a lowercase ASCII letter
    // AND NOT a lowercase ISO-8859-1 letter (excluding '÷' / 0xF7)
    bool is_not_lowercase = (ch < 'a' || ch > 'z') && 
                            (ch < 0xE0 || ch > 0xFE || ch == 0xF7);

    if (is_not_lowercase)
        return ch;
    
    // Convert to uppercase by subtracting 32 (the difference between 'a' and 'A')
    return ch - 32;
}