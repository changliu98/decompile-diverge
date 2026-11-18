StateResult __cdecl handle_before_attr_name_state(
        GumboParser *parser,
        GumboTokenizerState *tokenizer,
        int c,
        GumboToken *output)
{
  StateResult result;

  switch ( c )
  {
    case -1:
      tokenizer_add_parse_error(parser, GUMBO_ERR_ATTR_NAME_EOF);
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_DATA);
      abandon_current_tag(parser);
      result = NEXT_CHAR;
      break;

    case 0:
      tokenizer_add_parse_error(parser, GUMBO_ERR_UTF8_NULL);
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_ATTR_NAME);
      append_char_to_temporary_buffer(parser, 0xFFFD); // 65533
      result = NEXT_CHAR;
      break;

    case 9:
    case 10:
    case 12:
    case 32:
      // Ignore whitespace characters (tab, newline, form feed, space)
      result = NEXT_CHAR;
      break;

    case 34: // '"'
    case 39: // '\''
    case 60: // '<'
    case 61: // '='
      tokenizer_add_parse_error(parser, GUMBO_ERR_ATTR_NAME_INVALID);
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_ATTR_NAME);
      append_char_to_tag_buffer(parser, ensure_lowercase(c), 1);
      result = NEXT_CHAR;
      break;

    case 47: // '/'
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_SELF_CLOSING_START_TAG);
      result = NEXT_CHAR;
      break;

    case 62: // '>'
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_DATA);
      result = emit_current_tag(parser, output);
      break;

    default:
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_ATTR_NAME);
      append_char_to_tag_buffer(parser, ensure_lowercase(c), 1);
      result = NEXT_CHAR;
      break;
  }

  return result;
}