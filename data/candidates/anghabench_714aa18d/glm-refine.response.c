bool is_valid_ref_char(char ch)
{
    unsigned char c = (unsigned char)ch;

    return c > ' '      // Must be a printable, non-space character
        && c != '*'     // Disallow asterisk
        && c != ':'     // Disallow colon
        && c != '?'     // Disallow question mark
        && (c < '[' || c > '\\') // Disallow '[' (91) and '\' (92)
        && c != '^'     // Disallow caret
        && c != '~';    // Disallow tilde
}