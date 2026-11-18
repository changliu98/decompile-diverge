css_token_t *css_lexer_next_token(css_lexer_t *lexer) {
  css_token_t *token = _css_lexer_next_token(lexer);
  if (token->value[0] == '@' && strstr(token->value, "font-face") == NULL) {
    token->is_at_rule = true;
  }
  if (!strcmp(token->value, "to")) {
    token->type = 22;
  } else if (!strcmp(token->value, "@media") ||
             !strcmp(token->value, "@page")) {
    token->type = 0;
  }
  return token;
}