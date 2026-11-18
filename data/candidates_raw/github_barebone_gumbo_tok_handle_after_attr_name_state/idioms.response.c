static enum StateResult lex_before_attribute_name(struct GumboParser *parser, struct GumboTokenizerState *state, int c, struct GumboToken *output) {
  enum StateResult result;
  switch (c) {
    case -1:
      tokenizer_add_parse_error(parser, GUMBO_ERR_ATTR_NAME_EOF);
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_DATA);
      abandon_current_tag(parser);
      result = NEXT_CHAR;
      break;
    case '\0':
      tokenizer_add_parse_error(parser, GUMBO_ERR_UTF8_NULL);
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_ATTR_NAME);
      append_char_to_temporary_buffer(parser, 0xfffd);
      result = NEXT_CHAR;
      break;
    case ' ':
    case '\t':
    case '\n':
    case '\f':
      result = NEXT_CHAR;
      break;
    case '<':
      tokenizer_add_parse_error(parser, GUMBO_ERR_ATTR_NAME_INVALID);
    case '>':
    case '/':
    case '=':
    case '\'':
    case '"':
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_ATTR_NAME);
      append_char_to_tag_buffer(parser, ensure_lowercase(c), 1);
      result = NEXT_CHAR;
      break;
    case ' ':
    case '\t':
    case '\n':
    case '\f':
      result = NEXT_CHAR;
      break;
  }
  return result;
}