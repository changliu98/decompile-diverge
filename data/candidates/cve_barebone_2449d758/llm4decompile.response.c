int pj_scan_get_char(pj_scanner *scanner)
{
    int c = *scanner->curptr;
    if (c == '\0') {
        pj_scan_syntax_err(scanner);
        return 0;
    }
    ++scanner->curptr;
    if (*scanner->curptr <= ' ' && scanner->skip_ws)
        pj_scan_skip_whitespace(scanner);
    return c;
}