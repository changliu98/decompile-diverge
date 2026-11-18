void css_lexer_advance(CSSLexer *lexer)
{
  // Check if the current position is within the valid range of the input string
  if ((ulong)lexer->i < lexer->len) {
    // Move the index forward by one character
    lexer->i++;
    // Update the current character to the next one in the input buffer
    lexer->c = lexer->value[lexer->i];
    
    // If the current character is a newline, increment the row counter and reset the column counter
    if (lexer->c == '\n') {
      lexer->row++;
      lexer->col = 0;
    }
    // Otherwise, simply increment the column counter
    else {
      lexer->col++;
    }
  }
  // If the index is out of range, print an error message
  else {
    printf("(CSS): Lexer out of range.\n");
  }
}