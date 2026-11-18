void int_to_str(uint number, char *buffer)
{
    // Iterate from the last digit position (index 9) down to the first (index 0)
    for (int index = 9; index >= 0; index--) {
        // Convert the last digit of n to its ASCII character representation
        buffer[index] = (number % 10) + '0';
        // Remove the last digit from n
        number /= 10;
    }
    // Null-terminate the string at index 10
    buffer[10] = '\0';
}