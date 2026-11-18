int __cdecl parse_matrix_header(char *line, int *width, int *height, double *scale, double *offset)
{
  int count = 0;
  const char *current_token = line;
  char *next_token;
  double header[4];

  // Strip carriage return (13) or newline (10) characters
  char *newline = strchr(line, '\r');
  if (newline || (newline = strchr(line, '\n')) != NULL)
    *newline = '\0';

  // Parse up to 4 space/tab delimited tokens
  for (next_token = vips_break_token(line, " \t"); 
       next_token && count < 4; 
       next_token = vips_break_token(next_token, " \t"))
  {
    if (vips_strtod(current_token, &header[count]))
    {
      vips_error("matload", "bad number \"%s\"", current_token);
      return -1;
    }
    ++count;
    current_token = next_token;
  }

  // Apply default values for optional scale and offset
  if (count < 4)
    header[3] = 0.0;
  if (count < 3)
    header[2] = 1.0;

  if (count < 2)
  {
    vips_error("matload", "%s", "no width / height");
    return -1;
  }

  // Validate that width and height are integers
  if (floor(header[0]) != header[0] || floor(header[1]) != header[1])
  {
    vips_error("mask2vips", "%s", "width / height not int");
    return -1;
  }

  *width = (int)header[0];
  *height = (int)header[1];

  // Validate dimensions bounds
  if (*width <= 0 || *width > 100000 || *height <= 0 || *height > 100000)
  {
    vips_error("mask2vips", "%s", "width / height out of range");
    return -1;
  }

  // Validate scale
  if (header[2] == 0.0)
  {
    vips_error("mask2vips", "%s", "zero scale");
    return -1;
  }

  *scale = header[2];
  *offset = header[3];

  return 0;
}