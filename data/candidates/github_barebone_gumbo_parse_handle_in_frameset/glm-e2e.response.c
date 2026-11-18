bool handle_in_frameset(void *parser, void *token) {
    int token_type = *(int *)token;

    if (token_type == 4) {
        insert_text_token(parser, token);
        return true;
    } else if (token_type == 3) {
        void *current_node = get_current_node(parser);
        append_comment_node(parser, current_node, token);
        return true;
    } else if (token_type == 0) {
        parser_add_parse_error(parser, token);
        ignore_token(parser);
        return false;
    } else if (tag_is(token, true, 0)) {
        return handle_in_body(parser, token);
    } else if (tag_is(token, true, 0x81)) {
        insert_element_from_token(parser, token);
        return true;
    } else if (tag_is(token, false, 0x81)) {
        if (node_html_tag_is(get_current_node(parser), 0)) {
            parser_add_parse_error(parser, token);
            ignore_token(parser);
            return false;
        }
        
        pop_current_node(parser);
        
        if (!is_fragment_parser(parser) && !node_html_tag_is(get_current_node(parser), 0x81)) {
            set_insertion_mode(parser, 0x14);
        }
        return true;
    } else if (tag_is(token, true, 0x80)) {
        insert_element_from_token(parser, token);
        pop_current_node(parser);
        acknowledge_self_closing_tag(parser);
        return true;
    } else if (tag_is(token, true, 0x82)) {
        return handle_in_head(parser, token);
    } else if (token_type == 8) {
        if (!node_html_tag_is(get_current_node(parser), 0)) {
            parser_add_parse_error(parser, token);
            return false;
        }
        return true;
    } else {
        parser_add_parse_error(parser, token);
        ignore_token(parser);
        return false;
    }
}