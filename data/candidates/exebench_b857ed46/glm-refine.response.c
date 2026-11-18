void __cdecl convert_human(size_t size, size_t *nsize, char *c)
{
  int unit_index; // Represents the power of 1024 (0 = Bytes, 1 = KB, 2 = MB, etc.)

  // Divide the size by 1024 until it is less than or equal to 1024 (0x400)
  unit_index = 0;
  while (size > 0x400)
  {
    size >>= 10; // Equivalent to size /= 1024
    ++unit_index;
  }

  // Assign the appropriate unit character based on the number of divisions
  switch (unit_index)
  {
    case 0:
      *c = ' ';  // Bytes (represented as a space)
      break;
    case 1:
      *c = 'K';  // Kilobytes
      break;
    case 2:
      *c = 'M';  // Megabytes
      break;
    case 3:
      *c = 'G';  // Gigabytes
      break;
    case 4:
      *c = 'T';  // Terabytes
      break;
    case 5:
      *c = 'P';  // Petabytes
      break;
    default:
      break;     // Fallback for sizes exceeding Petabytes
  }

  // Output the scaled-down size
  *nsize = size;
}