int pj_scan_get_char(struct pj_scanner *scanner) {
    int ret_char;
    int cur_char;

    // Read the current character from the scanner's cursor
    cur_char = *(signed char *)scanner->curptr;

    if (cur_char == 0) {
        // End of string reached
        pj_scan_syntax_err(scanner);
        ret_char = 0;
    } else {
        // Advance the cursor
        scanner->curptr++;
        
        // Check if the next character is a whitespace character
        // (ASCII <= 32 covers space, tab, newline, carriage return, etc.)
        if (*(signed char *)scanner->curptr <= 32 && scanner->skip_ws != 0) {
            pj_scan_skip_whitespace(scanner);
        }
        ret_char = cur_char;
    }

    return ret_char;
}