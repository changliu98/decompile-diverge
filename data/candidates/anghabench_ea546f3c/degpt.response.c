void insert_dle(uchar *output_buffer, uchar *input_buffer, int byte_count)
{
    // Iterate through 'count' bytes from source to destination
    while (byte_count--) {
        // Copy the current byte from source to destination
        *output_buffer = *input_buffer;
        
        // If the current byte is the DLE (Data Link Escape) character
        if (*input_buffer == DLE) {
            // Insert an additional DLE byte immediately after the current one
            output_buffer[1] = DLE;
            // Advance destination pointer by 2 bytes (original + inserted DLE)
            output_buffer += 2;
        } else {
            // Advance destination pointer by 1 byte
            output_buffer += 1;
        }
        // Advance source pointer by 1 byte
        input_buffer += 1;
    }
}