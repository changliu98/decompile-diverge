static bool handle_in_frameset(GumboParser* parser, GumboToken* token) {
  if (token->type == GUMBO_TOKEN_WHITESPACE) {
    insert_text_token(parser, token);
    return true;
  }
  if (token->type == GUMBO_TOKEN_COMMENT) {
    append_comment_node(parser, get_current_node(parser), token);
    return true;
  }
  if (token->type == GUMBO_TOKEN_DOCTYPE) {
    parser_add_parse_error(parser, token);
    ignore_token(parser);
    return false;
  }
  if (tag_is(token, true, GUMBO_TAG_BODY)) {
    return handle_in_body(parser, token);
  }
  if (tag_is(token, true, GUMBO_TAG_FRAMESET)) {
    insert_element_from_token(parser, token);
    return true;
  }
  if (tag_is(token, false, GUMBO_TAG_FRAMESET)) {
    if (node_html_tag_is(get_current_node(parser), GUMBO_TAG_BODY)) {
      parser_add_parse_error(parser, token);
      ignore_token(parser);
      return false;
    }
    pop_current_node(parser);
    if (!is_fragment_parser(parser) &&
        !node_html_tag_is(get_current_node(parser), GUMBO_TAG_FRAMESET)) {
      set_insertion_mode(parser, GUMBO_INSERTION_MODE_IN_HEAD);
    }
    return true;
  }
  if (tag_is(token, true, GUMBO_TAG_NOFRAMES)) {
    insert_element_from_token(parser, token);
    pop_current_node(parser);
    acknowledge_self_closing_tag(parser);
    return true;
  }
  if (tag_is(token, true, GUMBO_TAG_HEAD)) {
    return handle_in_head(parser, token);
  }
  if (token->type == GUMBO_TOKEN_EOF) {
    if (node_html_tag_is(get_current_node(parser), GUMBO_TAG_BODY)) {
      return true;
    }
    parser_add_parse_error(parser, token);
    return false;
  }
  parser_add_parse_error(parser, token);
  ignore_token(parser);
  return false;
}