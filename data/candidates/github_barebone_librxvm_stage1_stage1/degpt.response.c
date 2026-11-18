int stage1(rxvm_t *program, char *source_text, ir_stack_t **result_stack)
{
    context_t parser_context;
    int error_code;
    int parse_state;
    int return_status;

    // Initialize the context and prepare the return stack
    return_status = stage1_init(&parser_context, result_stack);
    if (-1 < return_status) {
        // Reset local fixup counters in the compiled structure
        program->lfixn = 0;
        program->lfix0 = 0;
        // Store the original input pointer for reference
        parser_context.orig = source_text;
        parse_state = 0;
        // Initialize the lexer
        lex_init();
        // Skip whitespace tokens (token 10) until a non-whitespace token is found
        while (parser_context.tok = lex(&source_text), parser_context.tok == 10) {
            parser_context.simple = source_text;
            parser_context.tok = 10;
        }
        // Check if the first token is EOF (0xf)
        if (parser_context.tok == 0xf) {
            // Check for simple local fixups in the original input
            check_simple_for_lfix(program, parser_context.orig);
            parser_context.simple = parser_context.orig;
            // Clean up context and free program stack
            stage1_cleanup(&parser_context);
            stack_free(parser_context.prog, inst_stack_cleanup);
            // Return null pointer for empty input
            *result_stack = (ir_stack_t *)0x0;
            return_status = 0;
        } else {
            // If there is a simple backlog, compile it
            if (parser_context.simple != (char *)0x0) {
                error_code = compile_simple_backlog(&parser_context);
                if (error_code < 0) {
                    return -0xe;
                }
                parser_context.simple = (char *)0x0;
            }
            // Main parsing loop
            do {
                // Handle lexer errors
                if (parser_context.tok < 0) {
                    stage1_err_cleanup(&parser_context);
                    return parser_context.tok;
                }
                // Process tokens based on current state
                if (parse_state == 0) {
                    error_code = stage1_main_state(&parser_context, &parse_state);
                    if (error_code < 0) {
                        stage1_err_cleanup(&parser_context);
                        return error_code;
                    }
                } else if ((parse_state == 1) && (error_code = stage1_charc_state(&parser_context, &parse_state), error_code < 0)) {
                    stage1_err_cleanup(&parser_context);
                    return error_code;
                }
                // Save last token and fetch next token
                parser_context.lasttok = parser_context.tok;
                parser_context.tok = lex(&source_text);
            } while (parser_context.tok != 0xf); // Loop until EOF
            // If last token was an operator (4) and buffer has data, append to program
            if ((parser_context.lasttok == 4) && (0 < (parser_context.buf)->size)) {
                stack_cat(parser_context.prog, parser_context.buf);
                free(parser_context.buf);
                stack_free_head(parser_context.parens);
            }
            // Check for unclosed character class state
            if (parse_state == 1) {
                stage1_err_cleanup(&parser_context);
                return_status = -6;
            } else if ((parser_context.parens)->head == (parser_context.parens)->tail) {
                // No unclosed parentheses, finalize the code
                lfix_stop();
                // Append pending parentheses data to program
                stack_cat(parser_context.prog, (parser_context.parens)->tail->data);
                // Attach any dangling alternatives
                attach_dangling_alt(&parser_context);
                // Generate final code
                return_status = code_match(&parser_context);
                if (-1 < return_status) {
                    // Set local fixup counts based on whether alternatives were seen
                    if (alternative_detected == 0) {
                        program->lfix0 = get_lfix0();
                        program->lfixn = get_lfixn();
                    } else {
                        program->lfix0 = 0;
                        program->lfixn = 0;
                    }
                    // Set the data size of the program stack
                    (parser_context.prog)->dsize = (uint)parser_context.chained;
                    // Clean up context and return success
                    stage1_cleanup(&parser_context);
                    return_status = 0;
                }
            } else {
                // Unclosed parentheses detected
                stage1_err_cleanup(&parser_context);
                return_status = -5;
            }
        }
    }
    return return_status;
}