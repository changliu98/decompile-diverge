void cwk_path_fix_root(char *buffer, size_t buffer_size, size_t length)
{
  if (path_style == CWK_STYLE_WINDOWS) {
    size_t i;
    size_t max = length < buffer_size ? length : buffer_size;
    for (i = 0; i < max; ++i) {
      if (cwk_path_is_separator(&buffer[i])) {
        buffer[i] = separators[0][0];
      }
    }
  }
}