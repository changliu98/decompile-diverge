// Opens the I2C device file and stores the file descriptor in the bus pointer
// Returns 0 on success, non-zero on failure
int openI2CBus(int *bus_fd, char *device_path)
{
    // Open the I2C device file with read-write access (O_RDWR = 2)
    int file_descriptor = open(device_path, 2);
    // Store the file descriptor in the output parameter
    *bus_fd = file_descriptor;
    // Return 0 if successful (fd >= 0), non-zero if failed (fd < 0)
    return file_descriptor < 0;
}