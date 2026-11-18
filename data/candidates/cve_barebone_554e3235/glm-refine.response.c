int __cdecl parse_matrix_header(char *line, int *width, int *height, double *scale, double *offset)
{
  int count = 0;
  const char *token = line;
  double header[4];

  // Strip carriage return (\r) or newline (\n) from the end of the line
  char *newline = strchr(line, '\r');
  if (!newline)
    newline = strchr(line, '\n');
  if (newline)
    *newline = '\0';

  // Parse up to 4 space/tab delimited tokens from the line
  for (char *next_token = vips_break_token(line, " \t"); 
       next_token && count < 4; 
       next_token = vips_break_token(next_token, " \t"))
  {
    if (vips_strtod(token, &header[count]))
    {
      vips_error("matload", "bad number \"%s\"", token);
      return -1;
    }
    count++;
    token = next_token;
  }

  // Apply default values for optional scale and offset if missing
  if (count < 4)
    header[3] = 0.0;  // Default offset
  if (count < 3)
    header[2] = 1.0;  // Default scale

  // Ensure we at least have width and height
  if (count < 2)
  {
    vips_error("matload", "%s", "no width / height");
    return -1;
  }

  // Validate that width and height are whole integers
  if (floor(header[0]) != header[0] || floor(header[1]) != header[1])
  {
    vips_error("mask2vips", "%s", "width / height not int");
    return -1;
  }

  // Cast dimensions to integer and validate bounds
  *width = (int)header[0];
  *height = (int)header[1];

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

  // Assign scale and offset to output pointers
  *scale = header[2];
  *offset = header[3];

  return 0;
}