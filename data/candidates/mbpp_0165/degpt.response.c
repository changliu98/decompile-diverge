int func0(char *input_string)
{
    int matching_count = 0; // Initialize counter for matching characters
    size_t string_length = strlen(input_string); // Get the length of the input string
    for (int index = 0; index < (int)string_length; index++) { // Iterate through each character in the string
        // Check if the current index matches the character's position in the alphabet
        // 0x41 is 'A' and 0x61 is 'a'
        // For uppercase: i == str1[i] - 'A' => str1[i] == 'A' + i
        // For lowercase: i == str1[i] - 'a' => str1[i] == 'a' + i
        if ((index == input_string[index] - 0x41) || (index == input_string[index] - 0x61)) {
            matching_count++; // Increment counter if condition is met
        }
    }
    return matching_count; // Return the total count of matching characters
}