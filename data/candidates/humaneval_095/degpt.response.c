int func0(char *(*dictionary) [2], int dict_size)
{
    // If the dictionary size is zero, return 0 (invalid/empty input)
    if (dict_size == 0) {
        return 0;
    }
    // Iterate through each entry in the dictionary
    for (int entry_index = 0; entry_index < dict_size; entry_index++) {
        // Get the first string from the current dictionary entry
        char *current_string = dictionary[entry_index][0];
        int has_uppercase = 0;
        int has_lowercase = 0;
        // Iterate through each character of the string
        for (int char_index = 0; current_string[char_index] != '\0'; char_index++) {
            // Get the ctype character classification table
            ushort **ctype_table = __ctype_b_loc();
            // Check if the character is NOT a letter (using ctype_b flags)
            // 0x400 is _ISupper | _ISlower combined, so if this bit is 0, it's not a letter
            if (((*ctype_table)[(int)(uint)(byte)current_string[char_index]] & 0x400) == 0) {
                // If any character is not a letter, return 0 (invalid)
                return 0;
            }
            // Check if the character is uppercase (0x100 is _ISupper)
            if (((*ctype_table)[(int)(uint)(byte)current_string[char_index]] & 0x100) != 0) {
                has_uppercase = 1;
            }
            // Check if the character is lowercase (0x200 is _ISlower)
            if (((*ctype_table)[(int)(uint)(byte)current_string[char_index]] & 0x200) != 0) {
                has_lowercase = 1;
            }
            // If both uppercase and lowercase flags are set for the same character,
            // this is invalid (should not happen for standard ASCII letters), return 0
            if (has_uppercase && has_lowercase) {
                return 0;
            }
        }
    }
    // All strings passed validation, return 1 (valid)
    return 1;
}