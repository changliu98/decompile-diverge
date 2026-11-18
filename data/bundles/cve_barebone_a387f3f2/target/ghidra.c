void pj_scan_skip_line(pj_scanner *scanner)

{
  void *pvVar1;
  char *s;
  pj_scanner *scanner_local;
  
  pvVar1 = pj_memchr(scanner->curptr,10,(long)scanner->end - (long)scanner->curptr);
  if (pvVar1 == (void *)0x0) {
    scanner->curptr = scanner->end;
  }
  else {
    scanner->start_line = (char *)((long)pvVar1 + 1);
    scanner->curptr = (char *)((long)pvVar1 + 1);
    scanner->line = scanner->line + 1;
  }
  return;
}