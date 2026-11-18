char * func0(char **input_strings, int string_count)
{
    char format_buffer[100]; // Buffer to hold formatted string for each pair
    int index; // Loop counter

    // Initialize the result string with an opening bracket
    strcpy(func0::res, "[");
    
    // Iterate through the test list in steps of 2 to process pairs
    for (index = 0; index < string_count; index += 2) {
        // Convert the two consecutive string elements to floats and format them
        snprintf(format_buffer, 100, "(%.2f, %.2f)", atof(input_strings[index]), atof(input_strings[index + 1]));
        
        // Append the formatted pair to the result string
        strcat(func0::res, format_buffer);
        
        // Add a comma and space separator if this is not the last pair
        if (index < string_count - 2) {
            strcat(func0::res, ", ");
        }
    }
    
    // Append the closing bracket to complete the array representation
    strcat(func0::res, "]");
    
    // Return the constructed string
    return func0::res;
}