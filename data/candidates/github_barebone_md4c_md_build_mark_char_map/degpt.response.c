void md_build_mark_char_map(MD_CTX *context)
{
    // Initialize the mark character map to all zeros
    memset(context->mark_char_map, 0, 0x100);

    // Mark common special characters that always require escaping or have special meaning
    context->mark_char_map[0x5c] = '\x01'; // Backslash '\'
    context->mark_char_map[0x2a] = '\x01'; // Asterisk '*'
    context->mark_char_map[0x5f] = '\x01'; // Underscore '_'
    context->mark_char_map[0x60] = '\x01'; // Backtick '`'
    context->mark_char_map[0x26] = '\x01'; // Ampersand '&'
    context->mark_char_map[0x3b] = '\x01'; // Semicolon ';'
    context->mark_char_map[0x3c] = '\x01'; // Less-than '<'
    context->mark_char_map[0x3e] = '\x01'; // Greater-than '>'
    context->mark_char_map[0x5b] = '\x01'; // Left bracket '['
    context->mark_char_map[0x21] = '\x01'; // Exclamation mark '!'
    context->mark_char_map[0x5d] = '\x01'; // Right bracket ']'
    context->mark_char_map[0] = '\x01';    // Null character

    // Conditionally mark characters based on parser flags
    if (context->parser.flags & 0x40200) context->mark_char_map[0x7e] = '\x01'; // Tilde '~'
    if (context->parser.flags & 0x20000) context->mark_char_map[0x5e] = '\x01'; // Caret '^'
    if (context->parser.flags & 0x1000) context->mark_char_map[0x24] = '\x01';  // Dollar sign '$'
    if (context->parser.flags & 0x200000) context->mark_char_map[0x3d] = '\x01'; // Equals '='
    if (context->parser.flags & 8) context->mark_char_map[0x40] = '\x01';       // At sign '@'
    if (context->parser.flags & 4) context->mark_char_map[0x3a] = '\x01';       // Colon ':'
    if (context->parser.flags & 0x400) context->mark_char_map[0x2e] = '\x01';   // Period '.'

    // Mark pipe character if any of the specified flags are set
    if ((context->parser.flags & 0x100) || (context->parser.flags & 0x2000) || (context->parser.flags & 0x10000)) context->mark_char_map[0x7c] = '\x01'; // Pipe '|'

    // If flag 1 is set, mark whitespace characters (space, tab, vertical tab, form feed)
    if (context->parser.flags & 1) {
        int char_code;
        for (char_code = 0; char_code < 0x100; char_code++) {
            if (char_code == 0x20 || char_code == 9 || char_code == 0xb || char_code == 0xc) {
                context->mark_char_map[char_code] = '\x01';
            }
        }
    }
}