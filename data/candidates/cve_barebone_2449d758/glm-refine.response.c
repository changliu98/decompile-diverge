int __cdecl pj_scan_get_char(pj_scanner *scanner)
{
  int chr;

  chr = *scanner->curptr;
  if (chr == 0)
  {
    pj_scan_syntax_err(scanner);
    return 0;
  }

  // Advance the current pointer
  scanner->curptr++;

  // If the new character is whitespace and whitespace skipping is enabled, skip it
  if (*scanner->curptr <= 32 && scanner->skip_ws)
  {
    pj_scan_skip_whitespace(scanner);
  }

  return chr;
}