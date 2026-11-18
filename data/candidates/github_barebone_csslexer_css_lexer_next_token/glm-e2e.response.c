CssToken *css_lexer_next_token(void *lexer) {
    CssToken *token = _css_lexer_next_token(lexer);
    
    // Check if the first character of the token's value is '@' (0x40)
    if (token->value[0] == '@') {
        // If the value does not contain the substring at 0x423b
        if (strstr(token->value, "some_string_1") == NULL) {
            token->flag = 1;
        }
    }
    
    // Compare the token's value with the string at 0x41ff
    if (strcmp(token->value, "some_string_2") == 0) {
        token->type = 0x16;
    } else {
        // Compare with the string at 0x4202
        if (strcmp(token->value, "some_string_3") == 0 || 
            strcmp(token->value, "some_string_4") == 0) {
            token->type = 0;
        }
    }
    
    return token;
}