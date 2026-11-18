int func0(int input_value)
{
    // Check if input is even; if so, print error and return -1
    if (input_value % 2 == 0) {
        printf("Invalid Input\n");
        return -1;
    }
    // Initialize counter for number of terms and sum accumulator
    int term_count = 0;
    int sum_of_odds = 0;
    // Iterate from n down to 1, decrementing by 2 (odd numbers only)
    for (int current_odd = input_value; current_odd > 0; current_odd -= 2) {
        // Increment the count of terms processed
        term_count++;
        // Add the current odd number to the sum
        sum_of_odds += current_odd;
    }
    // Return the average of the odd numbers from 1 to n
    return sum_of_odds / term_count;
}