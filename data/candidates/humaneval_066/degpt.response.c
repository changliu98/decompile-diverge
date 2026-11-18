int func0(char *input_string)
{
    int uppercase_ascii_sum = 0;
    // Iterate through each character in the string until the null terminator
    for (int char_index = 0; input_string[char_index] != '\0'; char_index++) {
        // Check if the character is an uppercase letter (ASCII range '@' to '[')
        if (input_string[char_index] > '@' && input_string[char_index] < '[') {
            // Add the ASCII value of the uppercase letter to the sum
            uppercase_ascii_sum += input_string[char_index];
        }
    }
    // Return the total sum of ASCII values of uppercase letters
    return uppercase_ascii_sum;
}