char func0(char *input_string)
{
    // Array to store frequency of each character (ASCII values 0-255)
    int char_counts[256] = {0};
    
    // Variable to track the maximum frequency found so far
    int highest_count = 0;
    
    // Variable to store the character with the maximum frequency
    char most_frequent_char = '\0';
    
    // Get the length of the input string
    int string_length = strlen(input_string);
    
    // Iterate through each character in the string
    for (int index = 0; index < string_length; index++) {
        // Increment the frequency count for the current character
        // Cast to unsigned char to handle potential negative values from signed char
        char_counts[(unsigned char)input_string[index]]++;
        
        // Check if the current character's frequency exceeds the maximum frequency found so far
        if (highest_count < char_counts[(unsigned char)input_string[index]]) {
            // Update the maximum frequency
            highest_count = char_counts[(unsigned char)input_string[index]];
            // Update the character with the highest frequency
            most_frequent_char = input_string[index];
        }
    }
    
    // Return the character that appears most frequently in the string
    return most_frequent_char;
}