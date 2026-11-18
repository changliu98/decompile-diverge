int match(Reinst *current_instruction, char *current_position, char *beginning_of_line, int match_flags, Resub *subexpression_results)
{
    Reclass *character_class;
    uint word_char_status;
    int result_code;
    bool is_word_boundary;
    bool previous_is_word_char;
    Rune current_rune;
    int subexpression_length;
    Resub temporary_results;
    Resub *unused_out;
    int unused_flags;
    char *unused_bol;
    char *unused_sp;
    Reinst *unused_pc;

    // Initialize local pointers to input parameters
    unused_sp = current_position;
    unused_pc = current_instruction;
    do {
        // Dispatch based on the current instruction opcode
        switch (unused_pc->opcode) {
        case '\0':
            // End of pattern: match successful
            return 1;
        case '\x01':
            // Nop: proceed to next instruction
            unused_pc = unused_pc->x;
            break;
        case '\x02':
            // Branch: try matching 'x' first. If it fails, try 'y'.
            memcpy(&temporary_results, subexpression_results, 0xa8);
            result_code = match(unused_pc->x, unused_sp, beginning_of_line, match_flags, &temporary_results);
            if (result_code != 0) {
                // If 'x' matched, update output and return success
                memcpy(subexpression_results, &temporary_results, 0xa8);
                return 1;
            }
            // If 'x' failed, proceed to 'y'
            unused_pc = unused_pc->y;
            break;
        case '\x03':
            // And: try matching 'x'. If it fails, return failure immediately.
            // If it succeeds, proceed to 'y'.
            result_code = match(unused_pc->x, unused_sp, beginning_of_line, match_flags, subexpression_results);
            if (result_code == 0) {
                return 0;
            }
            unused_pc = unused_pc->y;
            break;
        case '\x04':
            // Backtrack: try matching 'x'. If it succeeds, return failure (backtrack).
            // If it fails, proceed to 'y'.
            memcpy(&temporary_results, subexpression_results, 0xa8);
            result_code = match(unused_pc->x, unused_sp, beginning_of_line, match_flags, &temporary_results);
            if (result_code != 0) {
                return 0;
            }
            unused_pc = unused_pc->y;
            break;
        case '\x05':
            // Match any character: consume one rune from input.
            result_code = chartorune(&current_rune, unused_sp);
            unused_sp = unused_sp + result_code;
            if (current_rune == 0) {
                return 0;
            }
            unused_pc = unused_pc + 1;
            break;
        case '\x06':
            // Match any character except newline: consume one rune.
            // Fail if the character is a newline.
            result_code = chartorune(&current_rune, unused_sp);
            unused_sp = unused_sp + result_code;
            if (current_rune == 0) {
                return 0;
            }
            result_code = isnewline((uint)current_rune);
            if (result_code != 0) {
                return 0;
            }
            unused_pc = unused_pc + 1;
            break;
        case '\a':
            // Match specific character 'c': consume one rune.
            // If case-insensitive flag is set, canonicalize the character before comparison.
            result_code = chartorune(&current_rune, unused_sp);
            unused_sp = unused_sp + result_code;
            if (current_rune == 0) {
                return 0;
            }
            if ((match_flags & 1U) != 0) {
                result_code = canon(current_rune);
                current_rune = (Rune)result_code;
            }
            if (current_rune != unused_pc->c) {
                return 0;
            }
            unused_pc = unused_pc + 1;
            break;
        case '\b':
            // Match character in class 'cc': consume one rune.
            // If case-insensitive flag is set, canonicalize before checking class membership.
            result_code = chartorune(&current_rune, unused_sp);
            unused_sp = unused_sp + result_code;
            if (current_rune == 0) {
                return 0;
            }
            if ((match_flags & 1U) == 0) {
                result_code = incclass(unused_pc->cc, current_rune);
                if (result_code == 0) {
                    return 0;
                }
            }
            else {
                character_class = unused_pc->cc;
                result_code = canon(current_rune);
                result_code = incclasscanon(character_class, (Rune)result_code);
                if (result_code == 0) {
                    return 0;
                }
            }
            unused_pc = unused_pc + 1;
            break;
        case '\t':
            // Match character NOT in class 'cc': consume one rune.
            // If case-insensitive flag is set, canonicalize before checking class membership.
            result_code = chartorune(&current_rune, unused_sp);
            unused_sp = unused_sp + result_code;
            if (current_rune == 0) {
                return 0;
            }
            if ((match_flags & 1U) == 0) {
                result_code = incclass(unused_pc->cc, current_rune);
                if (result_code != 0) {
                    return 0;
                }
            }
            else {
                character_class = unused_pc->cc;
                result_code = canon(current_rune);
                result_code = incclasscanon(character_class, (Rune)result_code);
                if (result_code != 0) {
                    return 0;
                }
            }
            unused_pc = unused_pc + 1;
            break;
        case '\n':
            // Match previously captured subexpression 'n':
            // Compare current input substring with the stored subexpression.
            subexpression_length = (int)subexpression_results->sub[unused_pc->n].ep - (int)subexpression_results->sub[unused_pc->n].sp;
            if ((match_flags & 1U) == 0) {
                result_code = strncmp(unused_sp, subexpression_results->sub[unused_pc->n].sp, (long)subexpression_length);
                if (result_code != 0) {
                    return 0;
                }
            }
            else {
                result_code = strncmpcanon(unused_sp, subexpression_results->sub[unused_pc->n].sp, subexpression_length);
                if (result_code != 0) {
                    return 0;
                }
            }
            if (0 < subexpression_length) {
                unused_sp = unused_sp + subexpression_length;
            }
            unused_pc = unused_pc + 1;
            break;
        case '\v':
            // Match beginning of line:
            // If at start of input or BOL flag is set, proceed.
            // Otherwise, check if previous character was newline (unless EOL flag is set).
            if ((unused_sp == beginning_of_line) && ((match_flags & 4U) == 0)) {
                unused_pc = unused_pc + 1;
            }
            else {
                if (((match_flags & 2U) == 0) ||
                    ((unused_sp <= beginning_of_line || (result_code = isnewline((int)unused_sp[-1]), result_code == 0)))) {
                    return 0;
                }
                unused_pc = unused_pc + 1;
            }
            break;
        case '\f':
            // Match end of line:
            // If at end of input or EOL flag is set, proceed.
            // Otherwise, check if current character is newline (unless BOL flag is set).
            if (*unused_sp == '\0') {
                unused_pc = unused_pc + 1;
            }
            else {
                if (((match_flags & 2U) == 0) || (result_code = isnewline((int)*unused_sp), result_code == 0)) {
                    return 0;
                }
                unused_pc = unused_pc + 1;
            }
            break;
        case '\r':
            // Match word boundary:
            // Check if current position is between a word char and a non-word char.
            previous_is_word_char = false;
            if (beginning_of_line < unused_sp) {
                result_code = iswordchar((int)unused_sp[-1]);
                previous_is_word_char = result_code != 0;
            }
            subexpression_length = (int)previous_is_word_char;
            word_char_status = iswordchar((int)*unused_sp);
            subexpression_length = word_char_status ^ subexpression_length;
            if (subexpression_length == 0) {
                return 0;
            }
            unused_pc = unused_pc + 1;
            break;
        case '\x0e':
            // Match non-word boundary:
            // Check if current position is between two word chars or two non-word chars.
            is_word_boundary = false;
            if (beginning_of_line < unused_sp) {
                result_code = iswordchar((int)unused_sp[-1]);
                is_word_boundary = result_code != 0;
            }
            subexpression_length = (int)is_word_boundary;
            result_code = iswordchar((int)*unused_sp);
            if (result_code != subexpression_length) {
                return 0;
            }
            unused_pc = unused_pc + 1;
            subexpression_length = 0;
            break;
        case '\x0f':
            // Set start of subexpression 'n' to current position
            subexpression_results->sub[unused_pc->n].sp = unused_sp;
            unused_pc = unused_pc + 1;
            break;
        case '\x10':
            // Set end of subexpression 'n' to current position
            subexpression_results->sub[unused_pc->n].ep = unused_sp;
            unused_pc = unused_pc + 1;
            break;
        default:
            // Unknown opcode: match failure
            return 0;
        }
    } while (true);
}