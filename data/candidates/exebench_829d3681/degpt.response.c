void word2string(uint number, char *output_buffer)
{
    // Handle the special case where the input value is zero
    if (number == 0) {
        output_buffer[0] = '0';
        output_buffer[1] = ' ';
        output_buffer[2] = '\0';
    } else {
        char *buffer_ptr = output_buffer;
        uint remaining_value = number;
        // Iterate through predefined magnitude constants to extract digits
        for (int magnitude_index = 0; magnitude_index < 5; magnitude_index++) {
            // Check if the current position is different from the buffer start
            // to determine if a digit should be written
            if (buffer_ptr + (ulong)remaining_value / (ulong)word2string::magnitudes[magnitude_index] != output_buffer) {
                // Convert the current digit to its character representation
                *buffer_ptr = (char)(remaining_value / word2string::magnitudes[magnitude_index]) + '0';
                buffer_ptr++;
                // Update the remaining value for the next iteration
                remaining_value %= word2string::magnitudes[magnitude_index];
            }
        }
        // Terminate the string with a space and null terminator
        *buffer_ptr = ' ';
        *(buffer_ptr + 1) = '\0';
    }
}