void css_lexer_advance(CSSLexer *lexer) {
  if (lexer->i < lexer->len) {
    lexer->i += 1;
    lexer->c = lexer->value[lexer->i];

    if (lexer->c == '\n') {
      lexer->row += 1;
      lexer->col = 0;
    } else  {
      lexer->col += 1;
    }
  } else {
    printf("(CSS): Lexer out of range.\n");
  }
}