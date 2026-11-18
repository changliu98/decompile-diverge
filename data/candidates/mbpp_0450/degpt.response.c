// Function to filter strings of a specific length from an array of strings
// Parameters:
//   str  - Array of strings to search through
//   n    - Number of strings in the array
//   l    - Target string length to match
//   size - Pointer to store the count of matching strings
// Returns:
//   Pointer to an array containing strings of length l
char ** filter_strings_by_length(char **strings, int num_strings, int target_length, int *match_count)
{
    int matching_count = 0; // Counter for strings matching the target length
    for (int index = 0; index < num_strings; index++) {
        // Check if the current string has the target length
        if (strlen(strings[index]) == (size_t)target_length) {
            // Add matching string to the result array
            func0::result[matching_count] = strings[index];
            matching_count++;
        }
    }
    // Store the count of matching strings
    *match_count = matching_count;
    // Return the array of matching strings
    return filter_strings_by_length::result;
}