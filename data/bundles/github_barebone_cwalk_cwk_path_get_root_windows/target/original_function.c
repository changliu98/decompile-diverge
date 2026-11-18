static void cwk_path_get_root_windows(const char *path, size_t *length)
{
  const char *c;
  bool is_device_path;

  // We can not determine the root if this is an empty string. So we set the
  // root to NULL and the length to zero and cancel the whole thing.
  c = path;
  *length = 0;
  if (!*c) {
    return;
  }

  // Now we have to verify whether this is a windows network path (UNC), which
  // we will consider our root.
  if (cwk_path_is_separator(c)) {
    ++c;

    // Check whether the path starts with a single backslash, which means this
    // is not a network path - just a normal path starting with a backslash.
    if (!cwk_path_is_separator(c)) {
      // Okay, this is not a network path but we still use the backslash as a
      // root.
      ++(*length);
      return;
    }

    // A device path is a path which starts with "\\." or "\\?". A device path
    // can be a UNC path as well, in which case it will take up one more
    // segment. So, this is a network or device path. Skip the previous
    // separator. Now we need to determine whether this is a device path. We
    // might advance one character here if the server name starts with a '?' or
    // a '.', but that's fine since we will search for a separator afterwards
    // anyway.
    ++c;
    is_device_path = (*c == '?' || *c == '.') && cwk_path_is_separator(++c);
    if (is_device_path) {
      // That's a device path, and the root must be either "\\.\" or "\\?\"
      // which is 4 characters long. (at least that's how Windows
      // GetFullPathName behaves.)
      *length = 4;
      return;
    }

    // We will grab anything up to the next stop. The next stop might be a '\0'
    // or another separator. That will be the server name.
    c = cwk_path_find_next_stop(c);

    // If this is a separator and not the end of a string we wil have to include
    // it. However, if this is a '\0' we must not skip it.
    while (cwk_path_is_separator(c)) {
      ++c;
    }

    // We are now skipping the shared folder name, which will end after the
    // next stop.
    c = cwk_path_find_next_stop(c);

    // Then there might be a separator at the end. We will include that as well,
    // it will mark the path as absolute.
    if (cwk_path_is_separator(c)) {
      ++c;
    }

    // Finally, calculate the size of the root.
    *length = (size_t)(c - path);
    return;
  }

  // Move to the next and check whether this is a colon.
  if (*++c == ':') {
    *length = 2;

    // Now check whether this is a backslash (or slash). If it is not, we could
    // assume that the next character is a '\0' if it is a valid path. However,
    // we will not assume that - since ':' is not valid in a path it must be a
    // mistake by the caller than. We will try to understand it anyway.
    if (cwk_path_is_separator(++c)) {
      *length = 3;
    }
  }
}