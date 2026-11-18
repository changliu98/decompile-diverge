void pj_scan_skip_line(pj_scanner *scan_ctx)
{
    // Find the next newline character (ASCII 10) in the current buffer range
    char *line_terminator = pj_memchr(scan_ctx->curptr, 10, (long)scan_ctx->end - (long)scan_ctx->curptr);
    
    // If no newline is found, move the current pointer to the end of the buffer
    if (line_terminator == NULL) {
        scan_ctx->curptr = scan_ctx->end;
    } else {
        // Set the start of the next line to the character immediately following the newline
        scan_ctx->start_line = line_terminator + 1;
        // Move the current pointer to the start of the next line
        scan_ctx->curptr = line_terminator + 1;
        // Increment the line counter
        scan_ctx->line++;
    }
}