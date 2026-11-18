static void cwk_path_fix_root(char *buffer, size_t buffer_size, size_t length)
{
  size_t i;

  // This only affects windows.
  if (path_style != CWK_STYLE_WINDOWS) {
    return;
  }

  // Make sure we are not writing further than we are actually allowed to.
  if (length > buffer_size) {
    length = buffer_size;
  }

  // Replace all forward slashes with backwards slashes. Since this is windows
  // we can't have any forward slashes in the root.
  for (i = 0; i < length; ++i) {
    if (cwk_path_is_separator(&buffer[i])) {
      buffer[i] = *separators[CWK_STYLE_WINDOWS];
    }
  }
}