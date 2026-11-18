// Function to calculate the number of digits in the sum of two longlong integers
int func0(longlong first_number, longlong second_number)
{
    int digit_count = 0; // Initialize digit counter to zero
    // Loop through the sum of num1 and num2, dividing by 10 in each iteration
    // until the number becomes zero, counting the number of digits
    for (longlong sum_value = first_number + second_number; 0 < sum_value; sum_value = sum_value / 10) {
        digit_count = digit_count + 1; // Increment the digit count for each iteration
    }
    return digit_count; // Return the total number of digits in the sum
}