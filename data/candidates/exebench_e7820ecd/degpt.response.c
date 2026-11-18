// Reads all requested bytes from file descriptor fd into buf.
// Returns the total number of bytes read, or 0 if no bytes could be read.
int read_all(int file_descriptor, uchar *buffer, int bytes_to_read) {
    int total_bytes_read = 0;          // Accumulator for total bytes read
    ssize_t bytes_read;              // Number of bytes read in the current iteration
    while (bytes_to_read > 0) {     // Continue until all requested bytes are read
        bytes_read = read(file_descriptor, buffer, bytes_to_read); // Attempt to read up to 'count' bytes
        if (bytes_read <= 0) break;    // Exit loop on error or end-of-file
        total_bytes_read += bytes_read;           // Add bytes read to total count
        buffer += bytes_read;             // Advance buffer pointer by bytes read
        bytes_to_read -= bytes_read;           // Decrease remaining bytes to read
    }
    return total_bytes_read;             // Return total bytes successfully read
}