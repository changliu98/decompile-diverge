int func0(char **string_list, int list_size)
{
    // Initialize min_val to the maximum possible integer value
    int minimum_value = 0x7fffffff;
    // Variable to hold the current parsed integer value
    int parsed_value;
    // Loop counter
    int index;

    // Iterate through each string in the list
    for (index = 0; index < list_size; index++) {
        // Parse the integer from the string and check if it's less than the current minimum
        if (__isoc99_sscanf(string_list[index], "%d", &parsed_value) != 0 && parsed_value < minimum_value) {
            // Update min_val if the current value is smaller
            minimum_value = parsed_value;
        }
    }
    // Return the minimum integer value found
    return minimum_value;
}