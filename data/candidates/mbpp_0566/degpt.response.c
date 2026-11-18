// Function to calculate the sum of digits of a non-negative integer n
int calculateSumOfDigits(int number)
{
    // Base case: if n is 0, return 0
    if (number == 0) {
        return 0;
    }
    // Recursive case: add the last digit of n to the sum of digits of the remaining part of n
    return number % 10 + calculateSumOfDigits(number / 10);
}