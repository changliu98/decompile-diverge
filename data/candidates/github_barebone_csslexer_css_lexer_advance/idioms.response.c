void css_lexer_advance(struct _CSSLexer *self)
{
  if (self->i < self->len)
  {
    self->c = self->value[++self->i];
    if (self->c == '\n')
    {
      self->row++;
      self->col = 0;
    }
    else
    {
      self->col++;
    }
  }
  else
  {
    printf("(CSS): Lexer out of range.\n");
  }
}