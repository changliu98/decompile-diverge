int func0(int input_number)
{
    int candidate_number;
    do {
        // Decrement num by 1 and store in x
        candidate_number = input_number - 1;
        // If x is less than 1, return 0 as no valid palindrome can be found
        if (candidate_number < 1) {
            return 0;
        }
        // Declare buffers for string representation and reversed string
        char number_string[12];
        char reversed_string[12];
        // Convert x to string
        sprintf(number_string, "%d", candidate_number);
        // Copy the string to rev_str for reversal
        strcpy(reversed_string, number_string);
        // Get the length of the reversed string
        int string_length = strlen(reversed_string);
        // Reverse the string in-place by swapping characters from both ends
        for (int index = 0; index < string_length / 2; index++) {
            char swap_temp = reversed_string[index];
            reversed_string[index] = reversed_string[string_length - 1 - index];
            reversed_string[string_length - 1 - index] = swap_temp;
        }
        // Update num to x for the next iteration
        input_number = candidate_number;
    } while (strcmp(number_string, reversed_string) != 0); // Continue until num_str is a palindrome (equal to its reverse)
    // Return the last valid x that formed a palindrome
    return candidate_number;
}