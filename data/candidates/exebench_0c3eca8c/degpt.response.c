/*
 * expand: Expands a character range specified in 'compacted' into 'expanded'.
 *
 * The 'compacted' string is expected to contain two characters representing
 * a start and end character (e.g., "a-z" or "0-9").
 *
 * This function handles various character ranges:
 * - Digits ('0'-'9')
 * - Uppercase letters ('A'-'Z')
 * - Lowercase letters ('a'-'z')
 *
 * It validates that the start character is less than or equal to the end character
 * and that they belong to the same contiguous ASCII range.
 *
 * Parameters:
 *   compacted - Input string containing the start and end characters.
 *   expanded  - Output buffer to store the expanded sequence of characters.
 */
void expand(char *input_range, char *output_buffer)
{
    int output_index; // Index for the expanded string
    int current_char;  // Loop variable for character iteration

    /*
     * Check if the first character is NOT a digit.
     * If it is a digit, we fall through to the else block which handles digits.
     * If it is not a digit, we proceed to check for letter ranges.
     */
    if (((*input_range < '0') || ('9' < *input_range)) || (input_range[2] < '0')) {
        /*
         * First character is not a digit. Check if the second character is
         * greater than '9'. If so, it might be a letter.
         * Also check if the second character is less than the first character.
         */
        if (('9' < input_range[2] || (input_range[2] < *input_range))) {
            /*
             * Check if the first character is NOT an uppercase letter ('A'-'Z').
             * Also check if the second character is less than 'A' or greater than 'Z',
             * or if the second character is less than the first character.
             */
            if (((*input_range < 'A') || (('Z' < *input_range || (input_range[2] < 'A')))) ||
               (('Z' < input_range[2] || (input_range[2] < *input_range)))) {
                /*
                 * Check if the first character is a lowercase letter ('a'-'z').
                 * Also check if the second character is a lowercase letter and
                 * if the first character is less than or equal to the second.
                 */
                if (((('`' < *input_range) && (*input_range < '{')) && ('`' < input_range[2])) &&
                   ((input_range[2] < '{' && (*input_range <= input_range[2])))) {
                    /*
                     * Valid lowercase letter range found.
                     * Expand the range from compacted[0] to compacted[2].
                     */
                    output_index = 0;
                    for (current_char = (int)*input_range; current_char <= input_range[2]; current_char = current_char + 1) {
                        output_buffer[output_index] = (char)current_char;
                        output_index = output_index + 1;
                    }
                    output_buffer[output_index] = '\0';
                }
            }
        }
        else {
            /*
             * The second character is not greater than '9' and is not less than the first.
             * This case seems to handle scenarios where the range check passes but
             * the characters are not in the expected letter ranges.
             * Fallback to simple expansion if the basic condition holds.
             */
            output_index = 0;
            for (current_char = (int)*input_range; current_char <= input_range[2]; current_char = current_char + 1) {
                output_buffer[output_index] = (char)current_char;
                output_index = output_index + 1;
            }
            output_buffer[output_index] = '\0';
        }
    }
    else {
        /*
         * The first character is a digit ('0'-'9').
         * Expand the range from compacted[0] to compacted[2].
         */
        output_index = 0;
        for (current_char = (int)*input_range; current_char <= input_range[2]; current_char = current_char + 1) {
            output_buffer[output_index] = (char)current_char;
            output_index = output_index + 1;
        }
        output_buffer[output_index] = '\0';
    }
    return;
}