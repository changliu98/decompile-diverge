CSSToken *__cdecl css_lexer_next_token(CSSLexer *lexer)
{
  CSSToken *tok; // [rsp+0h] [rbp-10h]

  tok = css_lexer_next_token(lexer);
  if ( *tok->value == 64 && !strstr(tok->value, "font-face") )
    tok->special = 1;
  if ( !strcmp(tok->value, "to") )
  {
    tok->type = 22;
  }
  else if ( !strcmp(tok->value, "@media") || !strcmp(tok->value, "@page") )
  {
    tok->type = 0;
  }
  return tok;
}