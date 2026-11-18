StateResult __cdecl handle_before_attr_name_state(
        GumboParser *parser,
        GumboTokenizerState *tokenizer,
        int c,
        GumboToken *output)
{
  int v4; // eax
  StateResult v8; // [rsp+3Ch] [rbp-4h]

  switch ( c )
  {
    case -1:
      tokenizer_add_parse_error(parser, GUMBO_ERR_ATTR_NAME_EOF);
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_DATA);
      abandon_current_tag(parser);
      v8 = NEXT_CHAR;
      break;
    case 0:
      tokenizer_add_parse_error(parser, GUMBO_ERR_UTF8_NULL);
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_ATTR_NAME);
      append_char_to_temporary_buffer(parser, 65533);
      v8 = NEXT_CHAR;
      break;
    case 9:
    case 10:
    case 12:
    case 32:
      v8 = NEXT_CHAR;
      break;
    case 34:
    case 39:
    case 60:
    case 61:
      tokenizer_add_parse_error(parser, GUMBO_ERR_ATTR_NAME_INVALID);
      goto LABEL_8;
    case 47:
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_SELF_CLOSING_START_TAG);
      v8 = NEXT_CHAR;
      break;
    case 62:
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_DATA);
      v8 = emit_current_tag(parser, output);
      break;
    default:
LABEL_8:
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_ATTR_NAME);
      v4 = ensure_lowercase(c);
      append_char_to_tag_buffer(parser, v4, 1);
      v8 = NEXT_CHAR;
      break;
  }
  return v8;
}