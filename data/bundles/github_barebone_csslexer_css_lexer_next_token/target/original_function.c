CSSToken *css_lexer_next_token(CSSLexer *lexer) {
  CSSToken *tok = _css_lexer_next_token(lexer);

  if (tok->value[0] == '@' && strstr(tok->value, "font-face") == 0) {
    tok->special = 1;
  }
  if (strcmp(tok->value, "to") == 0)
    tok->type = TOKEN_STATEMENT;
  else if (strcmp(tok->value, "@media") == 0 ||
           strcmp(tok->value, "@page") == 0)
    tok->type = TOKEN_ID;

  return tok;
}