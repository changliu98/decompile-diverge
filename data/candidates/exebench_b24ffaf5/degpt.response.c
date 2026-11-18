int OS_file_open(unsigned_long *file_handle, char *filename)
{
    // Open the file specified by p_filename with default flags (read-only)
    int file_descriptor = open(filename, 0);
    // Store the file descriptor in the output parameter
    *file_handle = (unsigned_long)file_descriptor;
    // Return 0 on success, or error code 0x1004 if the file could not be opened
    return (file_descriptor == -1) ? 0x1004 : 0;
}