int func0(int input_number)
{
    // Check if the input number is even
    if (input_number % 2 == 0) {
        int iteration_count = 0; // Initialize counter for the number of iterations
        int sum_of_evens = 0;    // Initialize sum accumulator
        // Iterate from n down to 2, decrementing by 2 each time (only even numbers)
        for (int current_even_number = input_number; 1 < current_even_number; current_even_number -= 2) {
            iteration_count++;   // Increment the count of processed numbers
            sum_of_evens += current_even_number; // Add the current number to the sum
        }
        // Return the average of the even numbers from n down to 2
        return sum_of_evens / iteration_count;
    } else {
        // Print error message for invalid (odd) input
        printf("Invalid Input\n");
        // Return -1 to indicate an error
        return -1;
    }
}