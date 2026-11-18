void css_lexer_advance(CSSLexer *lexer)

{
  CSSLexer *lexer_local;
  
  if ((ulong)lexer->i < lexer->len) {
    lexer->i = lexer->i + 1;
    lexer->c = lexer->value[lexer->i];
    if (lexer->c == '\n') {
      lexer->row = lexer->row + 1;
      lexer->col = 0;
    }
    else {
      lexer->col = lexer->col + 1;
    }
  }
  else {
    printf("(CSS): Lexer out of range.\n");
  }
  return;
}