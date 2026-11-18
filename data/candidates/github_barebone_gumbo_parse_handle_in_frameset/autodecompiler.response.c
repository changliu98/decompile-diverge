int handle_in_frameset(struct Parser *parser, struct Token *token)
{
    int result;

    if (token->type == 4) {
        insert_text_token(parser, token);
        result = 1;
    } else if (token->type == 3) {
        append_comment_node(parser, get_current_node(parser), token);
        result = 1;
    } else if (token->type == 0) {
        parser_add_parse_error(parser, token);
        ignore_token(parser);
        result = 0;
    } else if (tag_is(token, 1, 0)) {
        result = handle_in_body(parser, token) & 1;
    } else if (tag_is(token, 1, 129)) {
        insert_element_from_token(parser, token);
        result = 1;
    } else if (tag_is(token, 0, 129)) {
        if (node_html_tag_is(get_current_node(parser), 0)) {
            parser_add_parse_error(parser, token);
            ignore_token(parser);
            result = 0;
        } else {
            pop_current_node(parser);

            if (!is_fragment_parser(parser) && !node_html_tag_is(get_current_node(parser), 129)) {
                set_insertion_mode(parser, 20);
            }

            result = 1;
        }
    } else if (tag_is(token, 1, 128)) {
        insert_element_from_token(parser, token);
        pop_current_node(parser);
        acknowledge_self_closing_tag(parser);
        result = 1;
    } else if (tag_is(token, 1, 130)) {
        result = handle_in_head(parser, token) & 1;
    } else if (token->type == 8) {
        if (!node_html_tag_is(get_current_node(parser), 0)) {
            parser_add_parse_error(parser, token);
            result = 0;
        } else {
            result = 1;
        }
    } else {
        parser_add_parse_error(parser, token);
        ignore_token(parser);
        result = 0;
    }

    return result & 1;
}