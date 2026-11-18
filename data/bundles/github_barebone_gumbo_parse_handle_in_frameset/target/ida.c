bool __cdecl handle_in_frameset(GumboParser *parser, GumboToken *token)
{
  GumboNode *current_node; // rax
  GumboNode *v3; // rax
  GumboNode *v4; // rax
  GumboNode *v5; // rax

  switch ( token->type )
  {
    case GUMBO_TOKEN_WHITESPACE:
      insert_text_token(parser, token);
      return 1;
    case GUMBO_TOKEN_COMMENT:
      current_node = get_current_node(parser);
      append_comment_node(parser, current_node, token);
      return 1;
    case GUMBO_TOKEN_DOCTYPE:
LABEL_25:
      parser_add_parse_error(parser, token);
      ignore_token(parser);
      return 0;
  }
  if ( tag_is(token, 1, GUMBO_TAG_HTML) )
    return handle_in_body(parser, token);
  if ( tag_is(token, 1, GUMBO_TAG_FRAMESET) )
  {
    insert_element_from_token(parser, token);
    return 1;
  }
  if ( tag_is(token, 0, GUMBO_TAG_FRAMESET) )
  {
    v3 = get_current_node(parser);
    if ( node_html_tag_is(v3, GUMBO_TAG_HTML) )
      goto LABEL_25;
    pop_current_node(parser);
    if ( !is_fragment_parser(parser) )
    {
      v4 = get_current_node(parser);
      if ( !node_html_tag_is(v4, GUMBO_TAG_FRAMESET) )
        set_insertion_mode(parser, GUMBO_INSERTION_MODE_AFTER_FRAMESET);
    }
    return 1;
  }
  else
  {
    if ( tag_is(token, 1, GUMBO_TAG_FRAME) )
    {
      insert_element_from_token(parser, token);
      pop_current_node(parser);
      acknowledge_self_closing_tag(parser);
      return 1;
    }
    if ( tag_is(token, 1, GUMBO_TAG_NOFRAMES) )
      return handle_in_head(parser, token);
    if ( token->type != GUMBO_TOKEN_EOF )
      goto LABEL_25;
    v5 = get_current_node(parser);
    if ( node_html_tag_is(v5, GUMBO_TAG_HTML) )
    {
      return 1;
    }
    else
    {
      parser_add_parse_error(parser, token);
      return 0;
    }
  }
}