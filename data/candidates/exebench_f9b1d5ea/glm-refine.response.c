int __cdecl descape(int *in, int *out)
{
  // Check if the first character is a backslash (92 == '\x5C')
  if ( *in != 92 )
  {
    // If not an escape sequence, copy both integers directly to output
    *out = *in;
    out[1] = in[1];
    return 0;
  }

  // Handle the escape character
  switch ( in[1] )
  {
    case '"':       out[1] = 34;  break;  // Double quote
    case '\'':      out[1] = 39;  break;  // Single quote
    case '?':       out[1] = 63;  break;  // Question mark
    case 'a':       out[1] = 7;   break;  // Alert (Bell)
    case 'b':       out[1] = 8;   break;  // Backspace
    case 'f':       out[1] = 12;  break;  // Form feed
    case 'n':       out[1] = 10;  break;  // Newline (Line feed)
    case 'r':       out[1] = 13;  break;  // Carriage return
    case 't':       out[1] = 9;   break;  // Horizontal tab
    case 'v':       out[1] = 11;  break;  // Vertical tab
    default:
      // If it's an unrecognized escape sequence, treat as normal characters
      *out = *in;
      out[1] = in[1];
      return 0;
  }

  // Return 1 on a successfully parsed escape sequence
  return 1;
}