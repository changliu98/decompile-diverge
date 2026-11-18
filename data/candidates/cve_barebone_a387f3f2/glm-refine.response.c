void __cdecl pj_scan_skip_line(pj_scanner *scanner)
{
  const char *s;

  // The decompiler mistakenly identified memchr as a complex BitMask constructor.
  // It is actually searching for a newline character ('\n' = 10) within the scanner's buffer.
  s = (const char *)memchr(scanner->curptr, '\n', (size_t)(scanner->end - scanner->curptr));
  
  if (s)
  {
    // If a newline is found, advance the current pointer and start of the next line past it
    scanner->curptr = s + 1;
    scanner->start_line = s + 1;
    ++scanner->line;
  }
  else
  {
    // If no newline is found, move the cursor to the end of the buffer
    scanner->curptr = scanner->end;
  }
}