int pj_scan_get_char(struct pj_scanner *scanner)
{
  int c = *scanner->curptr;
  if (c == 0) {
    pj_sscan_eof(scanner);
    return 0;
  }
  scanner->curptr++;
  if (scanner->curptr < scanner->end && *scanner->curptr <= ' ' &&
      scanner->skip_ws) {
    pj_sscan_ws(scanner);
  }
  return c;
}