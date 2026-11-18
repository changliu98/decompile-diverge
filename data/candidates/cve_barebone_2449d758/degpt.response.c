int pj_scan_get_char(pj_scanner *pScanner)
{
  // Get the current character from the scanner's current position
  int currentChar = (int)*pScanner->curptr;
  
  // Check if the current character is a null terminator (end of string)
  if (currentChar == 0) {
    // Report a syntax error if end of string is reached unexpectedly
    pj_scan_syntax_err(pScanner);
    currentChar = 0;
  }
  else {
    // Move the scanner's current pointer to the next character
    pScanner->curptr++;
    
    // If whitespace skipping is enabled and the next character is a whitespace character,
    // skip all consecutive whitespace characters
    if ((*pScanner->curptr < '!') && (pScanner->skip_ws != 0)) {
      pj_scan_skip_whitespace(pScanner);
    }
  }
  
  // Return the character that was read
  return currentChar;
}