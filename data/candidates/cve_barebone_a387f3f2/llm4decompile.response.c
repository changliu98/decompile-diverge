void pj_scan_skip_line(pj_scanner *scanner)
{
    const char *p;

    p = pj_memchr(scanner->curptr, '\n', scanner->end - scanner->curptr);
    if (p != NULL) {
        scanner->curptr = scanner->start_line = p + 1;
        ++scanner->line;
    } else {
        scanner->curptr = scanner->end;
    }
}