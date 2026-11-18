char *gf_bt_get_next(GF_BTParser *parser, int skip_dot) {
    int keep_going = 1;
    int in_quotes = 0;
    int i = 0;

    gf_bt_check_line(parser);

    while (keep_going) {
        char c = parser->buf[parser->pos + i];

        if (c == '"') {
            in_quotes = !in_quotes;
            parser->pos++;
            if (parser->pos + i == parser->line_size) {
                break;
            }
        } else if (!in_quotes) {
            switch (c) {
                case 0:
                case '\t':
                case '\n':
                case ' ':
                case ',':
                case '[':
                case ']':
                case '{':
                case '}':
                    keep_going = 0;
                    break;
                case '.':
                    if (skip_dot) {
                        keep_going = 0;
                    }
                    break;
                default:
                    break;
            }

            if (!keep_going) {
                break;
            }
        }

        parser->token[i] = parser->buf[parser->pos + i];
        i++;
        if (parser->pos + i == parser->line_size) {
            break;
        }
    }

    parser->token[i] = '\0';
    parser->pos += i;
    return parser->token;
}