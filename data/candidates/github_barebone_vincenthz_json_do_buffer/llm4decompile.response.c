int do_buffer(json_parser *parser)
{
    int r;

    if (parser->type >= JSON_INT && parser->type <= JSON_FLOAT) {
        r = do_callback_withbuf(parser, parser->type);
        if (r)
            return r;
    }
    parser->buffer_offset = 0;
    return 0;
}