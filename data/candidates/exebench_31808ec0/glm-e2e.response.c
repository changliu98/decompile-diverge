void trataCoordenadas(const char *coord, int *x, int *y) {
    // Extract the first character (column letter) and convert to 0-based index
    // 'a' -> 0, 'b' -> 1, etc.
    *y = coord[0] - 'a';
    
    // Check if the 4th character (index 3) is null terminator or a newline
    if (coord[3] == '\0' || coord[3] == '\n') {
        // Single digit row: extract 3rd character (index 2) and convert to 0-based index
        // '1' -> 0, '2' -> 1, etc.
        *x = coord[2] - '1';
    } else {
        // Double digit row: parse the 3rd and 4th characters as an integer, then subtract 1
        *x = (coord[2] - '0') * 10 + (coord[3] - '0') - 1;
    }
}