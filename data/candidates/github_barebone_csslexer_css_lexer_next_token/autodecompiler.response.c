void css_lexer_next_token(struct _css_lexer *lexer)
{
    struct _css_token *token;

    token = _css_lexer_next_token(lexer);
    if (((token->str[0]) == '@') && !strstr(token->str, "font-face"))
        token->type = 1;
    if (!strcmp(token->str, "to"))
        token->type = 22;
    else if (!strcmp(token->str, "@media") || !strcmp(token->str, "@page"))
        token->type = 0;
}