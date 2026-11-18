char *__cdecl parse_content_length(char *buffer, char *end, int *length)
{
  char *p;
  int size;
  int number;

  // Skip leading HTTP header folding and whitespace
  while (buffer < end)
  {
    if (*buffer == ' ' || *buffer == '\t')
    {
      buffer++;
    }
    else if (*buffer == '\r' && buffer + 1 < end && buffer[1] == '\n')
    {
      buffer++;
    }
    else if (*buffer == '\n' && buffer + 1 < end && (buffer[1] == ' ' || buffer[1] == '\t'))
    {
      buffer++;
    }
    else
    {
      break;
    }
  }

  if (buffer == end)
    return NULL;

  size = 0;
  number = 0;

  // Parse the integer value for Content-Length
  while (buffer < end && *buffer >= '0' && *buffer <= '9')
  {
    number = *buffer + 10 * number - '0';
    if (number < 0)
      return NULL;
    size++;
    buffer++;
  }

  if (buffer == end || !size)
    return NULL;

  // Skip trailing whitespace and folding
  while (buffer < end)
  {
    if (*buffer == ' ' || *buffer == '\t')
    {
      buffer++;
    }
    else if (*buffer == '\n' && buffer + 1 < end && (buffer[1] == ' ' || buffer[1] == '\t'))
    {
      buffer++;
    }
    else
    {
      break;
    }
  }

  if (buffer == end)
    return NULL;

  p = buffer + 1;
  // Expect a newline (LF) or carriage return + newline (CRLF) to terminate the header line
  if (*buffer != '\n')
  {
    if (*buffer != '\r')
      return NULL;
    p = buffer + 2;
    if (p > end || *(buffer + 1) != '\n')
      return NULL;
  }

  *length = number;
  return p;
}