// Closes the file descriptor pointed to by fd and sets it to -1 to prevent double-close errors.
void closep(int *file_descriptor)
{
  // Only close if the file descriptor is valid (not already closed)
  if (*file_descriptor != -1) {
    close(*file_descriptor);
    // Mark the file descriptor as closed to avoid accidental reuse
    *file_descriptor = -1;
  }
}