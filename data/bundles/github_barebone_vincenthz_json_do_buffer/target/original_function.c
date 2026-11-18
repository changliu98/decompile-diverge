static int do_buffer(json_parser *parser)
{
	int ret = 0;

	switch (parser->type) {
	case JSON_KEY: case JSON_STRING:
	case JSON_FLOAT: case JSON_INT:
	case JSON_NULL: case JSON_TRUE: case JSON_FALSE:
		ret = do_callback_withbuf(parser, parser->type);
		if (ret)
			return ret;
		break;
	default:
		break;
	}
	parser->buffer_offset = 0;
	return ret;
}