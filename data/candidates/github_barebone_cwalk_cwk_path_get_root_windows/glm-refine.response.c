void __cdecl cwk_path_get_root_windows(const char *path, size_t *length)
{
  const char *cursor;
  const char *segment_start;
  const char *segment_end;

  *length = 0;
  
  // If the path is empty, the root length is 0
  if (!*path) {
    return;
  }

  if (cwk_path_is_separator(path)) 
  {
    // Path starts with a separator (e.g., "\...")
    if (cwk_path_is_separator(path + 1)) 
    {
      // Path starts with a double separator (e.g., "\\...")
      // This indicates a network path or a special device path.
      
      // Check for device path prefixes: "\\?" or "\\."
      if (path[2] == '?' || path[2] == '.') 
      {
        cursor = path + 3;
        if (cwk_path_is_separator(cursor)) 
        {
          // Found a device path separator: "\\?\" or "\\.\" (length 4)
          *length = 4;
          return;
        }
      } 
      else 
      {
        cursor = path + 2;
      }

      // If it wasn't a device path with a separator, it's a UNC path.
      // We need to find the end of the server name and the share name.
      // Example: "\\server\share\..."
      
      // Skip past the server name
      segment_start = cwk_path_find_next_stop(cursor);
      
      // Skip any consecutive separators after the server name
      while (cwk_path_is_separator(segment_start)) {
        ++segment_start;
      }
      
      // Find the end of the share name
      segment_end = cwk_path_find_next_stop(segment_start);
      
      // Include the trailing separator after the share name if it exists
      if (cwk_path_is_separator(segment_end)) {
        ++segment_end;
      }
      
      *length = segment_end - path;
    } 
    else 
    {
      // Path starts with a single separator (e.g. "\folder")
      *length = 1;
    }
  } 
  else if (path[1] == ':') 
  {
    // Path starts with a drive letter (e.g., "C:...")
    *length = 2;
    
    // Check for drive root separator (e.g., "C:\")
    if (cwk_path_is_separator(path + 2)) {
      *length = 3;
    }
  }
}