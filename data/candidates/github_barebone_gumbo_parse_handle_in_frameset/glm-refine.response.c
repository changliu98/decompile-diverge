bool __cdecl handle_in_frameset(GumboParser *parser, GumboToken *token)
{
  GumboNode *current_node;

  switch ( token->type )
  {
    case GUMBO_TOKEN_WHITESPACE:
      insert_text_token(parser, token);
      return true;

    case GUMBO_TOKEN_COMMENT:
      current_node = get_current_node(parser);
      append_comment_node(parser, current_node, token);
      return true;

    case GUMBO_TOKEN_DOCTYPE:
      parser_add_parse_error(parser, token);
      ignore_token(parser);
      return false;
  }

  if ( tag_is(token, 1, GUMBO_TAG_HTML) )
    return handle_in_body(parser, token);

  if ( tag_is(token, 1, GUMBO_TAG_FRAMESET) )
  {
    insert_element_from_token(parser, token);
    return true;
  }

  if ( tag_is(token, 0, GUMBO_TAG_FRAMESET) )
  {
    current_node = get_current_node(parser);
    if ( node_html_tag_is(current_node, GUMBO_TAG_HTML) )
    {
      parser_add_parse_error(parser, token);
      ignore_token(parser);
      return false;
    }

    pop_current_node(parser);

    if ( !is_fragment_parser(parser) )
    {
      current_node = get_current_node(parser);
      if ( !node_html_tag_is(current_node, GUMBO_TAG_FRAMESET) )
        set_insertion_mode(parser, GUMBO_INSERTION_MODE_AFTER_FRAMESET);
    }
    return true;
  }

  if ( tag_is(token, 1, GUMBO_TAG_FRAME) )
  {
    insert_element_from_token(parser, token);
    pop_current_node(parser);
    acknowledge_self_closing_tag(parser);
    return true;
  }

  if ( tag_is(token, 1, GUMBO_TAG_NOFRAMES) )
    return handle_in_head(parser, token);

  if ( token->type == GUMBO_TOKEN_EOF )
  {
    current_node = get_current_node(parser);
    if ( node_html_tag_is(current_node, GUMBO_TAG_HTML) )
      return true;

    parser_add_parse_error(parser, token);
    return false;
  }

  parser_add_parse_error(parser, token);
  ignore_token(parser);
  return false;
}