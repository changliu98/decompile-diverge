char *__cdecl gf_bt_get_next(GF_BTParser *parser, Bool point_break)
{
    s32 i = 0;
    bool has_quote = false;
    bool go = true;

    gf_bt_check_line(parser);

    do
    {
        // Skip and track double quotes ('"')
        while (parser->line_buffer[parser->line_pos + i] == '"')
        {
            has_quote = !has_quote;
            parser->line_pos++;
            if (parser->line_pos + i == parser->line_size)
                goto end_of_token;
        }

        // If inside a quote, blindly copy the character without checking for delimiters
        if (!has_quote)
        {
            char c = parser->line_buffer[parser->line_pos + i];
            
            // Check for null terminator, tab (9), newline (10), carriage return (13), space (32), or comma (44)
            if (c == '\0' || (unsigned int)(c - '\t') < 2 || c == '\r' || c == ' ' || c == ',')
            {
                go = false;
            }
            // Check for brackets and braces: '[' (91), ']' (93), '{' (123), '}' (125)
            else if (c == '[' || c == ']' || c == '{' || c == '}')
            {
                go = false;
            }
            // Check for dot '.' (46)
            else if (c == '.')
            {
                if (point_break)
                    go = false;
            }
        }

        if (!go)
            break;

        // Copy character to current buffer
        parser->cur_buffer[i] = parser->line_buffer[parser->line_pos + i];
        i++;
    }
    while (parser->line_pos + i != parser->line_size);

end_of_token:
    parser->cur_buffer[i] = '\0';
    parser->line_pos += i;
    return parser->cur_buffer;
}