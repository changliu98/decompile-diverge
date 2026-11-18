void SaltTextAway(struct Document *doc, int slot_idx, int *start_line_ptr, int *end_line_ptr) {
    int start_line = *start_line_ptr;
    int end_line = *end_line_ptr;
    int start_col = *start_line_ptr; // Inferred from assembly offset -0x54
    int end_col = *end_line_ptr;     // Inferred from assembly offset -0x5c
    int total_length = 0;
    int i;
    int has_newline;
    char *buffer;
    char *ptr;
    struct DocSlot *slot;

    // Bounds check for slot index
    if (slot_idx < 0 || slot_idx >= 12) {
        return;
    }

    slot = &doc->slots[slot_idx];

    // Swap columns if start_col is greater than end_col
    if (start_line == end_line && start_col > end_col) {
        int temp = start_col;
        start_col = end_col;
        end_col = temp;
    }

    end_col--;

    // Calculate required buffer length
    if (end_line == start_line) {
        total_length = Length(doc, start_line, start_col, end_col);
    } else {
        total_length += Length(doc, start_line, start_col, doc->slots[0].length) + 1;
        
        for (i = start_line + 1; i < end_line; i++) {
            total_length += Length(doc, i, 0, doc->slots[0].length) + 1;
        }
        
        if (end_col >= 0) {
            total_length += Length(doc, end_line, 0, end_col);
        }
    }

    // Double the required size if the document flag is set
    if (doc->flag != 0) {
        total_length <<= 2; // Equivalent to total_length *= 4
    }

    if (total_length < 0) {
        return;
    }

    // Allocate or reuse buffer
    if ((unsigned int)slot->length <= (unsigned int)total_length) {
        buffer = (char *)malloc(total_length + 1);
        if (!buffer) {
            SysError(0x47); // 'G' - likely an out-of-memory error code
        }
        free(slot->text);
        slot->text = buffer;
        slot->length = total_length + 1;
    } else {
        buffer = slot->text;
    }

    if (!buffer) {
        return;
    }

    buffer[total_length] = '\0';
    ptr = buffer;
    has_newline = 0;

    // Copy text into the buffer
    if (end_line == start_line) {
        ptr = SaveText(doc, end_line, start_col, end_col, ptr, &has_newline);
    } else {
        ptr = SaveText(doc, start_line, start_col, doc->slots[0].length, ptr, &has_newline);
        if (has_newline != 0) {
            *ptr++ = '\n';
        }
        
        for (i = start_line + 1; i < end_line; i++) {
            ptr = SaveText(doc, i, 0, doc->slots[0].length, ptr, &has_newline);
            if (has_newline != 0) {
                *ptr++ = '\n';
            }
        }
        
        if (end_col >= 0) {
            ptr = SaveText(doc, end_line, 0, end_col, ptr, &has_newline);
        }
    }

    *ptr = '\0';
    slot->length = ptr - buffer;
}