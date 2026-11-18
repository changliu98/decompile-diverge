StateResult
handle_after_attr_name_state
          (GumboParser *parser,GumboTokenizerState *tokenizer,int c,GumboToken *output)

{
  int codepoint;
  GumboToken *output_local;
  int c_local;
  GumboTokenizerState *tokenizer_local;
  GumboParser *parser_local;
  StateResult local_c;
  
  switch(c) {
  case 0:
    tokenizer_add_parse_error(parser,GUMBO_ERR_UTF8_NULL);
    gumbo_tokenizer_set_state(parser,GUMBO_LEX_ATTR_NAME);
    append_char_to_temporary_buffer(parser,0xfffd);
    local_c = NEXT_CHAR;
    break;
  case 9:
  case 10:
  case 0xc:
  case 0x20:
    local_c = NEXT_CHAR;
    break;
  case 0x22:
  case 0x27:
  case 0x3c:
    tokenizer_add_parse_error(parser,GUMBO_ERR_ATTR_NAME_INVALID);
  default:
    gumbo_tokenizer_set_state(parser,GUMBO_LEX_ATTR_NAME);
    codepoint = ensure_lowercase(c);
    append_char_to_tag_buffer(parser,codepoint,true);
    local_c = NEXT_CHAR;
    break;
  case 0x2f:
    gumbo_tokenizer_set_state(parser,GUMBO_LEX_SELF_CLOSING_START_TAG);
    local_c = NEXT_CHAR;
    break;
  case 0x3d:
    gumbo_tokenizer_set_state(parser,GUMBO_LEX_BEFORE_ATTR_VALUE);
    local_c = NEXT_CHAR;
    break;
  case 0x3e:
    gumbo_tokenizer_set_state(parser,GUMBO_LEX_DATA);
    local_c = emit_current_tag(parser,output);
    break;
  case -1:
    tokenizer_add_parse_error(parser,GUMBO_ERR_ATTR_NAME_EOF);
    gumbo_tokenizer_set_state(parser,GUMBO_LEX_DATA);
    abandon_current_tag(parser);
    local_c = NEXT_CHAR;
  }
  return local_c;
}