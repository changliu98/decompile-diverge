char * func0(char *N)
{
    // Calculate the length of the input string N
    size_t stringLength = strlen(N);
    
    // Get the last character of the string
    char lastChar = N[stringLength - 1];
    
    // Check if the last character is an even digit or an even hexadecimal letter
    // Even digits: 0, 2, 4, 6, 8
    // Even hex letters: A (10), C (12), E (14)
    if (lastChar == '0' || lastChar == '2' || lastChar == '4' || lastChar == '6' || lastChar == '8' ||
        lastChar == 'A' || lastChar == 'C' || lastChar == 'E') {
        // Return "Even" if the last character represents an even value
        return "Even";
    } else {
        // Return "Odd" otherwise
        return "Odd";
    }
}