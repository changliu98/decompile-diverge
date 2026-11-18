CSSToken * css_lexer_next_token(CSSLexer *lexer_ptr)
{
    // Fetch the next token from the lexer
    CSSToken *current_token = _css_lexer_next_token(lexer_ptr);
    
    // Mark token as special if it starts with '@' but is not a font-face rule
    if (current_token->value[0] == '@' && strstr(current_token->value, "font-face") == NULL) {
        current_token->special = 1;
    }
    
    // Assign specific token types based on value
    if (strcmp(current_token->value, "to") == 0) {
        // "to" is treated as a statement token
        current_token->type = TOKEN_STATEMENT;
    } else if (strcmp(current_token->value, "@media") == 0 || strcmp(current_token->value, "@page") == 0) {
        // "@media" and "@page" are treated as ID tokens
        current_token->type = TOKEN_ID;
    }
    
    return current_token;
}