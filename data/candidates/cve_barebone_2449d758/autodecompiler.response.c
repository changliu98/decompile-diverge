static int pj_scan_get_char(pj_scanner *scanner)
{
    int c;
    int retval;

    c = *scanner->curptr;

    if (c == 0) {

        pj_scan_syntax_err(scanner);
        retval = 0;

    } else {

        ++scanner->curptr;


        switch (*scanner->curptr) {
        case ' ':
        case '\t':
        case '\n':
        case '\r':

            if (scanner->options.keep_whitespace) {
                pj_scan_skip_whitespace(scanner);
            }
            break;
        }

        retval = c;
    }

    return retval;
}