int func0(char *sourceString, char *targetString)
{
    int mismatchCount = 0;
    // Iterate through str1 until the null terminator is reached
    for (int index = 0; sourceString[index] != '\0'; index++) {
        // If characters at the same position differ, increment the mismatch count
        if (sourceString[index] != targetString[index]) {
            mismatchCount++;
        }
    }
    // If the count of mismatches is even, return half of it; otherwise, return -1
    return (mismatchCount % 2 == 0) ? mismatchCount / 2 : -1;
}