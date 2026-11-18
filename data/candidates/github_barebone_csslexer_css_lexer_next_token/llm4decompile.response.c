CSSToken *
css_lexer_next_token (CSSLexer *lexer)
{
  CSSToken *token = _css_lexer_next_token (lexer);

  if (token->value[0] == '@' && strstr (token->value, "font-face") == NULL)
    token->special = 1;

  if (!strcmp (token->value, "to"))
    token->type = TOKEN_STATEMENT;
  else if (!strcmp (token->value, "@media") || !strcmp (token->value, "@page"))
    token->type = TOKEN_ID;

  return token;
}