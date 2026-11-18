static StateResult handle_after_attr_name_state(GumboParser* parser,
                                                GumboTokenizerState* tokenizer,
                                                int c,
                                                GumboToken* output) {
  switch (c) {
    case '>':
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_DATA);
      return emit_current_tag(parser, output);
    case '=':
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_BEFORE_ATTR_VALUE);
      return NEXT_CHAR;
    case '/':
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_SELF_CLOSING_START_TAG);
      return NEXT_CHAR;
    case '\'':
    case '"':
    case '<':
      tokenizer_add_parse_error(parser, GUMBO_ERR_ATTR_APOS_NOT_SUPPORTED);
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_ATTR_NAME);
      append_char_to_tag_buffer(parser, ensure_lowercase(c), true);
      return NEXT_CHAR;
    case '\t':
    case '\n':
    case '\f':
    case ' ':
      return NEXT_CHAR;
    case '\0':
      tokenizer_add_parse_error(parser, GUMBO_ERR_UTF8_NULL);
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_ATTR_NAME);
      append_char_to_temporary_buffer(parser, 0xFFFD);
      return NEXT_CHAR;
    case -1:
      tokenizer_add_parse_error(parser, GUMBO_ERR_ATTR_NAME_EOF);
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_DATA);
      abandon_current_tag(parser);
      return NEXT_CHAR;
    default:
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_ATTR_NAME);
      append_char_to_tag_buffer(parser, ensure_lowercase(c), true);
      return NEXT_CHAR;
  }
}