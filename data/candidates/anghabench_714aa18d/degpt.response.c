int is_valid_ref_char(char character)
{
    // Reject control characters (ASCII values less than 0x21)
    if ((unsigned char)character < 0x21) {
        return 0;
    }
    int charValue = (int)character;
    // Reject '*', ':', and '?' characters
    if (((charValue == 0x2a) || (charValue == 0x3a)) || (charValue == 0x3f)) {
        return 0;
    }
    // Reject '[', ']', '^', and '~' characters
    // Note: (iVar1 - 0x5bU < 2) checks if ch is '[' (0x5b) or ']' (0x5c)
    if (((charValue - 0x5bU < 2) || (charValue == 0x5e)) || (charValue == 0x7e)) {
        return 0;
    }
    return 1;
}