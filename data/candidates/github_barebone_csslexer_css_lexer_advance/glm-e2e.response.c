void css_lexer_advance(CssLexer *lexer) {
    if (lexer->position >= lexer->length) {
        printf("css_lexer_advance: out of bounds\n"); // The exact string depends on your binary's .rodata
        return;
    }

    lexer->position += 1;
    lexer->current_char = lexer->input[lexer->position];

    if (lexer->current_char == '\n') {
        lexer->line += 1;
        lexer->column = 0;
    } else {
        lexer->column += 1;
    }
}