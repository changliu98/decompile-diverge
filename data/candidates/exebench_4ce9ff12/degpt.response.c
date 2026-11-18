// Calculates the length of the previous character in the buffer.
// Parameters:
//   buf     - Pointer to the buffer containing the string.
//   buf_len - Length of the buffer.
//   pos     - Current position in the buffer.
//   col_len - Pointer to store the column length of the previous character.
// Returns:
//   The length of the previous character (always 1 in this default implementation).
size_t defaultPrevCharLen(char *buffer, size_t buffer_length, size_t current_position, size_t *column_length)
{
  // If col_len is not NULL, set it to 1.
  if (column_length != (size_t *)0x0) {
    *column_length = 1;
  }
  // Return the default character length of 1.
  return 1;
}