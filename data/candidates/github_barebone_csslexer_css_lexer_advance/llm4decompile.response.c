void css_lexer_advance(CSSLexer *lexer) {
    if (lexer->i < lexer->len) {
        lexer->c = lexer->value[++lexer->i];

        if (lexer->c == '\n') {
            lexer->row++;
            lexer->col = 0;
        } else {
            lexer->col++;
        }
    } else {
        printf("(CSS): Lexer out of range.\n");
    }
}