int func0(int lowerBound, int upperBound)
{
    int validDigitCount = 0; // Initialize counter for valid numbers
    for (int currentNumber = lowerBound; currentNumber <= upperBound; currentNumber++) { // Iterate through the range [L, R]
        if (currentNumber < 10 || currentNumber > 15) { // Check if i is outside the range [10, 15]
            if (currentNumber > 15) { // Only process numbers greater than 15
                int tempNumber = currentNumber; // Copy i to k for digit processing
                while (tempNumber != 0) { // Process each hexadecimal digit of k
                    if (tempNumber % 16 > 9) { // Check if the current hex digit is A-F (10-15)
                        validDigitCount++; // Increment count for each such digit
                    }
                    tempNumber /= 16; // Move to the next hex digit
                }
            }
        } else {
            validDigitCount++; // Increment count for numbers in the range [10, 15]
        }
    }
    return validDigitCount; // Return the total count
}