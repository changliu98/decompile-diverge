static int gumbo__consume_tag_name(struct GumboTokenizer *tokenizer, struct GumboInput *input, int c, struct GumboVector *output) {
  int return_value;
  switch (c) {
    case '\t':
    case '\n':
    case '\f':
    case ' ':
      return_value = 2;
      break;
    case '/':
      gumbo_tokenizer_set_state(tokenizer, 42);
      return_value = 2;
      break;
    case '>':
      gumbo_tokenizer_set_state(tokenizer, 0);
      return_value = emit_current_tag(tokenizer, output);
      break;
    case '\0':
      tokenizer_add_parse_error(tokenizer, 2);
      gumbo_tokenizer_set_state(tokenizer, 34);
      append_char_to_temporary_buffer(tokenizer, 0xFFFD);
      return_value = 2;
      break;
    case -1:
      tokenizer_add_parse_error(tokenizer, 15);
      gumbo_tokenizer_set_state(tokenizer, 0);
      abandon_current_tag(tokenizer);
      return_value = 2;
      break;
    case '"':
    case '\'':
    case '<':
    case '=':
      tokenizer_add_parse_error(tokenizer, 16);
    default:
      gumbo_tokenizer_set_state(tokenizer, 34);
      append_char_to_tag_buffer(tokenizer, ensure_lowercase(c), true);
      return_value = 2;
  }
  return return_value;
}