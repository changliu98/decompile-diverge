void css_lexer_advance(css_lexer_t* lexer) {
  if (lexer->index < lexer->length) {
    lexer->current = lexer->source[++lexer->index];
    if (lexer->current == '\n') {
      lexer->line++;
      lexer->column = 0;
    } else {
      lexer->column++;
    }
  } else {
    printf("(CSS): Lexer out of range.\n");
  }
}