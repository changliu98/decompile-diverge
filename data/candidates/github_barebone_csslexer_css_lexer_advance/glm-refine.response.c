void __cdecl css_lexer_advance(CSSLexer *lexer)
{
  // Boundary check: Ensure we do not read past the allocated/buffered length
  if (lexer->i >= lexer->len)
  {
    printf("(CSS): Lexer out of range.\n");
  }
  else
  {
    // Pre-increment index and fetch the next character from the buffer
    lexer->c = lexer->value[++lexer->i];

    // Check for newline character (ASCII 10)
    if (lexer->c == '\n')
    {
      ++lexer->row;
      lexer->col = 0LL;  // Explicitly reset column to 0 (long long)
    }
    else
    {
      ++lexer->col;
    }
  }
}