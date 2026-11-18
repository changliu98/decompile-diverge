CSSToken *__cdecl css_lexer_next_token(CSSLexer *lexer)
{
  CSSToken *tok;

  // Retrieve the base token from the core lexer implementation
  tok = css_lexer_next_token(lexer);

  // Check if the token is an at-rule (starts with '@')
  if ( *tok->value == CHAR_AT_SYMBOL )
  {
    // If it's an at-rule but NOT "@font-face", flag it as special
    if ( !strstr(tok->value, "font-face") )
    {
      tok->special = 1;
    }
  }

  // Remap token types based on specific string values
  if ( !strcmp(tok->value, "to") )
  {
    tok->type = TOKEN_TYPE_TO;
  }
  else if ( !strcmp(tok->value, "@media") || !strcmp(tok->value, "@page") )
  {
    tok->type = TOKEN_TYPE_AT_RULE;
  }

  return tok;
}