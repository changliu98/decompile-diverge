BYTE __cdecl revchar(char ch)
{
    BYTE original_ch = ch;

    // Uppercase letters 'A'-'Z' map to 0-25
    if (ch >= 'A' && ch <= 'Z')
        return ch - 'A';

    // Lowercase letters 'a'-'z' map to 26-51
    if (ch >= 'a' && ch <= 'z')
        return ch - 'a' + 26;

    // Digits '0'-'9' map to 52-61
    if (ch >= '0' && ch <= '9')
        return ch - '0' + 52;

    // '+' maps to 62
    if (ch == '+')
        return 62;

    // '/' maps to 63
    if (ch == '/')
        return 63;

    // Return the original character if it's not a valid Base64 character
    return original_ch;
}