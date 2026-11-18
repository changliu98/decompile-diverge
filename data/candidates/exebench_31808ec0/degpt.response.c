void trataCoordenadas(char *input_line, int *col_index, int *row_index)
{
    // Convert the first character (letter) to a 0-based vertical index (e.g., 'a' -> 0, 'b' -> 1)
    *row_index = *input_line - 0x61;
    
    // Check if the horizontal coordinate is a single digit (length 3 or 4 with newline)
    if (input_line[3] == '\0' || input_line[3] == '\n') {
        // Single digit horizontal coordinate: convert character to 0-based index
        *col_index = input_line[2] - 0x31;
    } else {
        // Two-digit horizontal coordinate: calculate value and convert to 0-based index
        *col_index = (input_line[2] - 0x30) * 10 + input_line[3] - 0x31;
    }
}