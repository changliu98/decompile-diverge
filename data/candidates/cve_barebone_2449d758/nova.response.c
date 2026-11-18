int pj_scan_get_char(struct lexer *lexer)
{
    int c = lexer->curr;

    if (!c) {
        lexer_get(lexer);
        c = 0;
    } else if (lexer->curr > 32 || lexer->eof) {
        lexer_backup(lexer);
    }

    return c;
}