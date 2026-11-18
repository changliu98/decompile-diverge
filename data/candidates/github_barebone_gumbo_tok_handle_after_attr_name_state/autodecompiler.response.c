static int handle_after_attr_name_state(struct GumboTokenizer *tokenizer, struct StringPiece *input, int c, GumboVector *output) {
  int output_size;
  switch (c) {
    case '\t':
    case '\n':
    case '\f':
    case ' ':
      output_size = 2;
      break;
    case '/':
      gumbo_tokenizer_set_state(tokenizer, 42);
      output_size = 2;
      break;
    case '=':
      gumbo_tokenizer_set_state(tokenizer, 36);
      output_size = 2;
      break;
    case '>':
      gumbo_tokenizer_set_state(tokenizer, 0);
      output_size = emit_current_tag(tokenizer, output);
      break;
    case '\0':
      tokenizer_add_parse_error(tokenizer, 2);
      gumbo_tokenizer_set_state(tokenizer, 34);
      append_char_to_temporary_buffer(tokenizer, 0xFFFD);
      output_size = 2;
      break;
    case '\x0B':
    case '\x0C':
    case '\x0D':
    case '\x10':
    case '\x11':
    case '\x12':
    case '\x13':
    case '\x14':
    case '\x15':
    case '\x16':
    case '\x17':
    case '\x18':
    case '\x19':
    case '\x1A':
    case '\x1B':
    case '\x1C':
    case '\x1D':
    case '\x1E':
    case '\x1F':
    case '\x7F':
      tokenizer_add_parse_error(tokenizer, 15);
      gumbo_tokenizer_set_state(tokenizer, 0);
      abandon_current_tag(tokenizer);
      output_size = 2;
      break;
    case '"':
    case '\'':
    case '<':
      tokenizer_add_parse_error(tokenizer, 16);
    default:
      gumbo_tokenizer_set_state(tokenizer, 34);
      append_char_to_tag_buffer(tokenizer, ensure_lowercase(c), true);
      output_size = 2;
  }
  return output_size;
}