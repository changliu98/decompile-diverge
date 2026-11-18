int __cdecl pj_scan_get_char(pj_scanner *scanner)
{
  int chr; // [rsp+Ch] [rbp-14h]

  chr = *scanner->curptr;
  if ( *scanner->curptr )
  {
    if ( *++scanner->curptr <= 32 && scanner->skip_ws )
      pj_scan_skip_whitespace(scanner);
    return chr;
  }
  else
  {
    pj_scan_syntax_err(scanner);
    return 0;
  }
}