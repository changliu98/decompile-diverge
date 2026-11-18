char * gf_bt_get_next(GF_BTParser *bt_parser, Bool break_on_decimal)
{
    int char_index = 0;
    bool inside_quotes = false;
    bool should_stop = true;

    // Ensure the current line buffer is valid and loaded
    gf_bt_check_line(bt_parser);

    do {
        while (should_stop) {
            char current_char = bt_parser->line_buffer[bt_parser->line_pos + char_index];
            // If a quote is encountered, toggle the quote state and break to outer loop
            if (current_char == '"') {
                break;
            }
            if (!inside_quotes) {
                unsigned char unsigned_char_value = (unsigned char)current_char;
                // Stop if end of string, whitespace, comma, or control characters
                if (current_char == '\0' || (unsigned_char_value - 9U < 2) || current_char == '\r' || current_char == ' ' || current_char == ',') {
                    should_stop = false;
                } else if (current_char == '.') {
                    // Stop at decimal point if point_break is enabled
                    if (break_on_decimal != GF_FALSE) {
                        should_stop = false;
                    }
                } else if (current_char == '[' || current_char == ']' || current_char == '{' || current_char == '}') {
                    // Stop at structural delimiters
                    should_stop = false;
                }
            }
            if (!should_stop) {
                break;
            }
            // Copy current character to the output buffer
            bt_parser->cur_buffer[char_index] = current_char;
            char_index++;
            // Check if we've reached the end of the current line buffer
            if (bt_parser->line_pos + char_index == bt_parser->line_size) {
                goto end;
            }
        }
        // Toggle quote state when a quote character is found
        inside_quotes = !inside_quotes;
        bt_parser->line_pos++;
    } while (bt_parser->line_pos + char_index != bt_parser->line_size);

end:
    // Null-terminate the resulting string
    bt_parser->cur_buffer[char_index] = '\0';
    // Update the parser's position to the end of the extracted token
    bt_parser->line_pos = char_index + bt_parser->line_pos;
    return bt_parser->cur_buffer;
}