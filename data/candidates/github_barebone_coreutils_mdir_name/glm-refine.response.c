char *__cdecl mdir_name(const char *file)
{
  char *dir;
  size_t length;

  // Get the length of the directory portion of the file path
  length = dir_len(file);

  // Allocate memory for the directory string.
  // If length > 0, we need 'length' bytes + 1 for the null terminator.
  // If length == 0, we need 1 byte for '.' + 1 for the null terminator.
  // The expression (length == 0) evaluates to 1 if true, 0 if false, 
  // which perfectly handles both allocation sizes.
  dir = (char *)malloc(length + (length == 0) + 1);
  
  if (dir == NULL)
    return NULL;

  // Copy the directory portion of the path into the new buffer
  memcpy(dir, file, length);

  // If the path has no directory component (e.g., "file.txt"), 
  // default to the current directory (".")
  if (length == 0)
  {
    *dir = '.';
    length = 1;
  }

  // Null-terminate the string
  dir[length] = '\0';

  return dir;
}