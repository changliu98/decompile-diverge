Main function decompilation
int handle_after_attr_name_state(GumboTokenizerState* tokenizer, void* output, int c, void* unused_or_ctx) {
    // The switch statement uses a jump table for ASCII characters from 0x00 to 0x3F
    switch (c) {
        case '\t': // 0x09
        case '\n': // 0x0A
        case '\f': // 0x0C
        case ' ':  // 0x20
            // Ignore the character
            break;

        case '/':  // 0x2F
            gumbo_tokenizer_set_state(tokenizer, 0x2A); // Self-closing start tag state
            break;

        case '=':  // 0x3D
            gumbo_tokenizer_set_state(tokenizer, 0x24); // Before attribute value state
            break;

        case '>':  // 0x3E
            gumbo_tokenizer_set_state(tokenizer, 0); // Data state
            return emit_current_tag(tokenizer, output);

        case '\0': // 0x00 (Null character)
            tokenizer_add_parse_error(tokenizer, 2);
            gumbo_tokenizer_set_state(tokenizer, 0x22); // Attribute value (unquoted) state
            append_char_to_temporary_buffer(tokenizer, 0xFFFD); // Unicode replacement character
            break;

        case -1:   // 0xFF (EOF, sign-extended to -1 or handled as unsigned 0xFFFFFFFF)
            tokenizer_add_parse_error(tokenizer, 0xF);
            gumbo_tokenizer_set_state(tokenizer, 0); // Data state
            abandon_current_tag(tokenizer);
            break;

        default:
            if (c >= 'A' && c <= 'Z') {
                // Uppercase ASCII characters
                tokenizer_add_parse_error(tokenizer, 0x10);
                gumbo_tokenizer_set_state(tokenizer, 0x22); // Attribute name state
                append_char_to_tag_buffer(tokenizer, ensure_lowercase(c), 1);
            } else {
                // Any other character not covered by the jump table (0x00 - 0x3F range)
                tokenizer_add_parse_error(tokenizer, 0x10);
                gumbo_tokenizer_set_state(tokenizer, 0x22); // Attribute name state
                append_char_to_tag_buffer(tokenizer, c, 1);
            }
            break;
    }

    return GUMBO_STATUS_CONTINUE;
}