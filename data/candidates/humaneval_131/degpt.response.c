int func0(int n)
{
    int product = 1; // Initialize product accumulator to 1
    bool found_odd_digit = false; // Flag to track if any odd digit is found
    for (int current_number = n; 0 < current_number; current_number = current_number / 10) {
        if ((current_number % 10) % 2 == 1) { // Check if the last digit is odd
            found_odd_digit = true; // Set flag to true since an odd digit was found
            product = (current_number % 10) * product; // Multiply the odd digit into the product
        }
    }
    return found_odd_digit ? product : 0; // Return product if any odd digit was found, otherwise return 0
}