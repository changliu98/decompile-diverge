void nextline(struct _pj_scanner *scanner)
{
  char *p = (char *)pj_strchr(scanner->curptr, '\n', scanner->end - scanner->curptr);
  if (p == ((void *)0)) {
    scanner->curptr = scanner->end;
  }
  else {
    scanner->start_line = p + 1;
    scanner->curptr = p + 1;
    scanner->line++;
  }
}