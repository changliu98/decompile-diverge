void pj_scan_skip_line(pj_scanner *scanner) {
    // Calculate the remaining length in the buffer
    size_t remaining = scanner->end - scanner->curptr;
    
    // Search for a newline character ('\n' = 0xa)
    char *newline_pos = (char *)pj_memchr(scanner->curptr, '\n', remaining);
    
    if (newline_pos == NULL) {
        // If no newline is found, advance the current pointer to the end
        scanner->curptr = scanner->end;
    } else {
        // If a newline is found, advance the pointer past the newline
        char *next_pos = newline_pos + 1;
        scanner->skip_curptr = next_pos;
        scanner->curptr = next_pos;
        
        // Increment the line counter
        scanner->line++;
    }
}