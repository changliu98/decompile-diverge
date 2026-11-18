int func0(int n)
{
    int sevenDigitCount = 0; // Initialize counter for numbers containing digit 7
    for (int currentNumber = 0; currentNumber < n; currentNumber++) { // Iterate through numbers from 0 to n-1
        if (currentNumber % 0xb == 0 || currentNumber % 0xd == 0) { // Check if i is divisible by 11 (0xb) or 13 (0xd)
            for (int digitExtractor = currentNumber; digitExtractor > 0; digitExtractor /= 10) { // Extract each digit of i
                if (digitExtractor % 10 == 7) { // Check if the current digit is 7
                    sevenDigitCount++; // Increment count for each occurrence of digit 7
                }
            }
        }
    }
    return sevenDigitCount; // Return total count of digit 7 in qualifying numbers
}