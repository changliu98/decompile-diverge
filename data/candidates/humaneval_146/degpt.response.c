int func0(int *numbers, int count)
{
    int validCount = 0; // Counter for numbers satisfying the condition
    for (int index = 0; index < count; index++) {
        if (numbers[index] > 10) { // Process only numbers greater than 10
            int firstDigit = numbers[index];
            while (firstDigit > 9) {
                firstDigit /= 10; // Extract the first digit of the number
            }
            // Check if both the first digit and the last digit are odd
            if (firstDigit % 2 == 1 && numbers[index] % 10 % 2 == 1) {
                validCount++;
            }
        }
    }
    return validCount; // Return the count of numbers with both first and last digits odd
}