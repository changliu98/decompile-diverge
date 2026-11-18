// Function to calculate the sum of all common divisors of two integers a and b
int func0(int num1, int num2)
{
    int common_divisor_sum = 0; // Initialize sum to store the total of common divisors
    int current_divisor = 1;   // Start checking divisors from 1
    // Determine the smaller of the two numbers to set the upper limit for divisor checking
    int upper_bound = (num1 < num2) ? num1 : num2;
    // Iterate from 1 up to the smaller number
    while (current_divisor <= upper_bound) {
        // Check if i is a divisor of both a and b
        if ((num1 % current_divisor == 0) && (num2 % current_divisor == 0)) {
            // If i is a common divisor, add it to the sum
            common_divisor_sum += current_divisor;
        }
        // Move to the next potential divisor
        current_divisor++;
    }
    // Return the calculated sum of common divisors
    return common_divisor_sum;
}