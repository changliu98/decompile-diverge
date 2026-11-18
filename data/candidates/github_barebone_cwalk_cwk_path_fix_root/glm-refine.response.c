void __cdecl cwk_path_fix_root(char *buffer, size_t buffer_size, size_t length)
{
  size_t i;
  size_t effective_length;

  // If path_style is set (non-zero), do nothing.
  if (path_style != 0) {
    return;
  }

  // Prevent out-of-bounds reading if the provided length exceeds the buffer size.
  effective_length = (length > buffer_size) ? buffer_size : length;

  // Iterate through the buffer and normalize separators.
  for (i = 0; i < effective_length; ++i) {
    if (cwk_path_is_separator(&buffer[i])) {
      // Overwrite any valid separator with the primary separator.
      buffer[i] = separators[0];
    }
  }
}