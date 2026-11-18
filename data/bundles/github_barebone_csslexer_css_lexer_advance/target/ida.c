void __cdecl css_lexer_advance(CSSLexer *lexer)
{
  if ( lexer->i >= lexer->len )
  {
    printf("(CSS): Lexer out of range.\n");
  }
  else
  {
    lexer->c = lexer->value[++lexer->i];
    if ( lexer->c == 10 )
    {
      ++lexer->row;
      lexer->col = 0LL;
    }
    else
    {
      ++lexer->col;
    }
  }
}