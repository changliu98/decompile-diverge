void func0(char *input_string, int *letter_count_ptr, int *digit_count_ptr)
{
    int letter_count = 0; // Counter for letters
    int digit_count = 0; // Counter for digits
    for (char *current_char_ptr = input_string; *current_char_ptr != '\0'; current_char_ptr++) {
        ushort **ctype_table_ptr = __ctype_b_loc(); // Get pointer to ctype table
        if (((*ctype_table_ptr)[(int)(uint)(byte)*current_char_ptr] & 0x800) == 0) { // Check if character is not a digit
            if (((*ctype_table_ptr)[(int)(uint)(byte)*current_char_ptr] & 0x400) != 0) { // Check if character is a letter
                letter_count++; // Increment letter count
            }
        } else {
            digit_count++; // Increment digit count
        }
    }
    *letter_count_ptr = letter_count; // Store letter count in output parameter
    *digit_count_ptr = digit_count; // Store digit count in output parameter
}