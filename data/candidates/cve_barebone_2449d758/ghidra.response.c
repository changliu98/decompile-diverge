int pj_scan_get_char(pj_scanner *scanner)

{
  int chr;
  pj_scanner *scanner_local;
  int local_c;
  
  local_c = (int)*scanner->curptr;
  if (local_c == 0) {
    pj_scan_syntax_err(scanner);
    local_c = 0;
  }
  else {
    scanner->curptr = scanner->curptr + 1;
    if ((*scanner->curptr < '!') && (scanner->skip_ws != 0)) {
      pj_scan_skip_whitespace(scanner);
    }
  }
  return local_c;
}