_Bool handle_in_frameset(GumboParser *parser,GumboToken *token)

{
  _Bool _Var1;
  GumboNode *pGVar2;
  GumboToken *token_local;
  GumboParser *parser_local;
  _Bool local_9;
  
  if (token->type == GUMBO_TOKEN_WHITESPACE) {
    insert_text_token(parser,token);
    local_9 = true;
  }
  else if (token->type == GUMBO_TOKEN_COMMENT) {
    pGVar2 = get_current_node(parser);
    append_comment_node(parser,pGVar2,token);
    local_9 = true;
  }
  else if (token->type == GUMBO_TOKEN_DOCTYPE) {
    parser_add_parse_error(parser,token);
    ignore_token(parser);
    local_9 = false;
  }
  else {
    _Var1 = tag_is(token,true,GUMBO_TAG_HTML);
    if (_Var1) {
      local_9 = handle_in_body(parser,token);
    }
    else {
      _Var1 = tag_is(token,true,GUMBO_TAG_FRAMESET);
      if (_Var1) {
        insert_element_from_token(parser,token);
        local_9 = true;
      }
      else {
        _Var1 = tag_is(token,false,GUMBO_TAG_FRAMESET);
        if (_Var1) {
          pGVar2 = get_current_node(parser);
          _Var1 = node_html_tag_is(pGVar2,GUMBO_TAG_HTML);
          if (_Var1) {
            parser_add_parse_error(parser,token);
            ignore_token(parser);
            local_9 = false;
          }
          else {
            pop_current_node(parser);
            _Var1 = is_fragment_parser(parser);
            if (!_Var1) {
              pGVar2 = get_current_node(parser);
              _Var1 = node_html_tag_is(pGVar2,GUMBO_TAG_FRAMESET);
              if (!_Var1) {
                set_insertion_mode(parser,GUMBO_INSERTION_MODE_AFTER_FRAMESET);
              }
            }
            local_9 = true;
          }
        }
        else {
          _Var1 = tag_is(token,true,GUMBO_TAG_FRAME);
          if (_Var1) {
            insert_element_from_token(parser,token);
            pop_current_node(parser);
            acknowledge_self_closing_tag(parser);
            local_9 = true;
          }
          else {
            _Var1 = tag_is(token,true,GUMBO_TAG_NOFRAMES);
            if (_Var1) {
              local_9 = handle_in_head(parser,token);
            }
            else if (token->type == GUMBO_TOKEN_EOF) {
              pGVar2 = get_current_node(parser);
              _Var1 = node_html_tag_is(pGVar2,GUMBO_TAG_HTML);
              if (_Var1) {
                local_9 = true;
              }
              else {
                parser_add_parse_error(parser,token);
                local_9 = false;
              }
            }
            else {
              parser_add_parse_error(parser,token);
              ignore_token(parser);
              local_9 = false;
            }
          }
        }
      }
    }
  }
  return local_9;
}