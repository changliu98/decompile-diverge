int affs_intl_toupper(int character)
{
    // Convert lowercase ASCII letters (a-z) and certain extended ASCII characters to uppercase
    // Handles standard ASCII lowercase (0x61-0x7a) and specific ISO-8859-1 characters (0xe0-0xfe, excluding 0xf7)
    if (((0x60 < character) && (character < 0x7b)) || ((0xdf < character) && (character < 0xff) && (character != 0xf7)))
    {
        // Subtract 0x20 to convert lowercase to uppercase
        character += -0x20;
    }
    return character;
}