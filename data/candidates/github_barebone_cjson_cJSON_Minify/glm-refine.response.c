void __cdecl cJSON_Minify(char *json)
{
  char current_char;
  char *write_ptr;
  char *read_ptr;

  if (!json) {
    return;
  }

  read_ptr = json;
  write_ptr = json;

  while (*read_ptr)
  {
    current_char = *read_ptr;

    // Check for whitespace characters (Tab, Newline, Carriage Return, Space)
    if (current_char == '\t' || current_char == '\n' || current_char == '\r' || current_char == ' ')
    {
      read_ptr++;
    }
    else if (current_char == '"')
    {
      minify_string(&read_ptr, &write_ptr);
    }
    else if (current_char == '/')
    {
      if (read_ptr[1] == '/')
      {
        skip_oneline_comment(&read_ptr);
      }
      else if (read_ptr[1] == '*')
      {
        skip_multiline_comment(&read_ptr);
      }
      else
      {
        read_ptr++;
      }
    }
    else
    {
      *write_ptr++ = *read_ptr++;
    }
  }

  *write_ptr = '\0';
}