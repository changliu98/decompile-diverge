struct CSSToken *css_lexer_next_token(struct CSSLexer *lex)
{
    struct CSSToken *token = ((void *)0);
    token = css_lexer_next_token(lex);
    if (token->value[0] == '@' && strstr(token->value, "font-face") == ((void *)0))
    {
        token->special = 1;
    }
    if (strcmp(token->value, "to") == 0)
    {
        token->type = CSS_TOKEN_TO;
    }
    else if (strcmp(token->value, "@media") == 0 || strcmp(token->value, "@page") == 0)
    {
        token->type = CSS_TOKEN_ATKEYWORD;
    }
    return token;
}