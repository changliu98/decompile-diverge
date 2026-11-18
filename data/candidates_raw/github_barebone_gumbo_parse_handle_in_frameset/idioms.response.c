static _Bool handle_in_head(struct GumboParser *parser, struct GumboToken *token) {
  switch (token->type) {
    case GUMBO_TOKEN_DOCTYPE:
    case GUMBO_TOKEN_EOF:
      break;
    case GUMBO_TOKEN_COMMENT:
      append_comment_node(parser, get_current_node(parser), token);
      break;
    case GUMBO_TOKEN_TEXT:
      insert_text_token(parser, token);
      break;
    case GUMBO_TOKEN_START:
      if (tag_is(token, 1, GUMBO_TAG_HTML))
        return handle_in_body(parser, token);
      if (tag_is(token, 1, GUMBO_TAG_FRAMESET)) {
        insert_element_from_token(parser, token);
        return 1;
      }
      if (tag_is(token, 0, GUMBO_TAG_FRAMESET)) {
        if (node_html_tag_is(get_current_node(parser), GUMBO_TAG_HTML))
          break;
        pop_current_node(parser);
        if (!is_fragment_parser(parser)) {
          if (!node_html_tag_is(get_current_node(parser),
                                 GUMBO_TAG_FRAMESET))
            set_insertion_mode(parser, GUMBO_INSERTION_MODE_AFTER_FRAMESET);
        }
        return 1;
      }
      if (tag_is(token, 1, GUMBO_TAG_FRAME)) {
        insert_element_from_token(parser, token);
        pop_current_node(parser);
        acknowledge_self_closing_tag(parser);
        return 1;
      }
      if (tag_is(token, 1, GUMBO_TAG_NOFRAMES))
        return handle_in_head(parser, token);
      break;
    case GUMBO_TOKEN_END:
      if (tag_is(token, 1, GUMBO_TAG_HTML))
        return handle_in_body(parser, token);
      if (tag_is(token, 1, GUMBO_TAG_HEAD))
        return handle_in_head(parser, token);
      if (tag_is(token, 1, GUMBO_TAG_TITLE))
        return handle_in_title(parser, token);
      if (tag_is(token, 1, GUMBO_TAG_BASE))
        return handle_in_head(parser, token);
      if (tag_is(token, 1, GUMBO_TAG_META))
        return handle_in_head(parser, token);
      if (tag_is(token, 1, GUMBO_TAG_LINK))
        return handle_in_head(parser, token);
      if (tag_is(token, 1, GUMBO_TAG_SCRIPT))
        return handle_in_head(parser, token);
      if (tag_is(token, 1, GUMBO_TAG_STYLE))
        return handle_in_head(parser, token);
      if (tag_is(token, 1, GUMBO_TAG_BODY))
        return handle_in_body(parser, token);
      if (tag_is(token, 1, GUMBO_TAG_FRAMESET))
        return handle_in_head(parser, token);
      if (tag_is(token, 1, GUMBO_TAG_FRAME))
        return handle_in_head(parser, token);
      if (tag_is(token, 1, GUMBO_TAG_NOFRAMES))
        return handle_in_head(parser, token);
      break;
  }
  parser_add_parse_error(parser, token);
  ignore_token(parser);
  return 0;
}