StateResult __cdecl handle_after_attr_name_state(
        GumboParser *parser,
        GumboTokenizerState *tokenizer,
        int c,
        GumboToken *output)
{
  StateResult result; 
  int lowercased_char;

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
      append_char_to_temporary_buffer(parser, 0xFFFD); // 65533 is the Unicode replacement character
      result = NEXT_CHAR;
      break;

    case 9:
    case 10:
    case 12:
    case 32:
      // Tab, Newline, Form Feed, and Space characters are ignored in this state
      result = NEXT_CHAR;
      break;

    case 34:
    case 39:
    case 60:
      // '"', '\'', and '<' are invalid characters here
      tokenizer_add_parse_error(parser, GUMBO_ERR_ATTR_NAME_INVALID);
      goto LABEL_DEFAULT;

    case 47:
      // '/' - Self-closing tag
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_SELF_CLOSING_START_TAG);
      result = NEXT_CHAR;
      break;

    case 61:
      // '=' - Transition to before attribute value state
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_BEFORE_ATTR_VALUE);
      result = NEXT_CHAR;
      break;

    case 62:
      // '>' - End of tag
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_DATA);
      result = emit_current_tag(parser, output);
      break;

    default:
LABEL_DEFAULT:
      // Any other character is treated as a new attribute name
      gumbo_tokenizer_set_state(parser, GUMBO_LEX_ATTR_NAME);
      lowercased_char = ensure_lowercase(c);
      append_char_to_tag_buffer(parser, lowercased_char, 1);
      result = NEXT_CHAR;
      break;
  }
  return result;
}