static void func0(struct lexer *lexer)
{
    if (lexer->pos < lexer->size) {
        lexer->c = lexer->text[lexer->pos++];

        if (lexer->c == '\n') {
            lexer->cur_line++;
            lexer->cur_col = 0;
        } else {
            lexer->cur_col++;
        }
    } else {
        error("unexpected EOF while scanning");
    }
}