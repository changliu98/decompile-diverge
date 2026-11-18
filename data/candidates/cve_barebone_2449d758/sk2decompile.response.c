static int pj_scan_get_char(pj_scanner_t *scan) {
  int c = *scan->p;
  if (c == '\0') {
    pj_scan_syntax_err(scan);
    return '\0';
  }
  scan->p++;
  if (*scan->p <= ' ' && scan->skip_ws) {
    pj_scan_skip_whitespace(scan);
  }
  return c;
}