static StateResult handle_before_attr_name_state(GumboParser* parser,
                                                 GumboTokenizerState* tokenizer,
                                                 int c, GumboToken* output) {
  switch (c) {
    case '>':
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_DATA);
      return emit_current_tag(parser, output);
    case '/':
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_SELF_CLOSING_START_TAG);
      return NEXT_CHAR;
    case '\t':
    case '\n':
    case '\f':
    case ' ':
      return NEXT_CHAR;
    case '"':
    case '\'':
    case '<':
    case '=':
      tokenizer_add_parse_error(parser, GUMBO_ERR_ATTR_NAME_INVALID_CHAR);
      break;
    case 0:
      tokenizer_add_parse_error(parser, GUMBO_ERR_ATTR_NAME_INVALID_NULL);
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_AFTER_ATTR_NAME);
      append_char_to_temporary_buffer(parser, 0xFFFD);
      return NEXT_CHAR;
    case -1:
      tokenizer_add_parse_error(parser, GUMBO_ERR_ATTR_NAME_INVALID_EOF);
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_DATA);
      abandon_current_tag(parser);
      return NEXT_CHAR;
    default:
      break;
  }
  gumbo_tokenizer_set_state(parser, GUMBO_LEX_AFTER_ATTR_NAME);
  append_char_to_tag_buffer(parser, ensure_lowercase(c), true);
  return NEXT_CHAR;
}