struct config gf_bt_get_next(struct config old_config, int is_test) {
    int i = 1;
    struct config new_config = old_config;
    int is_quote = 0;
    int is_comment = 0;
    while (1) {
        while (new_config.start_pos + i!= new_config.end_pos) {
            if (is_quote) {
                if (new_config.content[new_config.start_pos + i] == '"') {
                    if (is_comment) {
                        is_comment = 0;
                    } else {
                        is_quote = 0;
                        if (new_config.start_pos + i + 1 ==
                            new_config.end_pos) {
                            break;
                        }
                    }
                }
            } else {
                char c = new_config.content[new_config.start_pos + i];
                if (c!= '\0') {
                    switch (c) {
                    case'':
                    case '\t':
                    case '\n':
                    case '\r':
                        new_config.content[i] = '\0';
                        new_config.start_pos += i + 1;
                        return new_config;
                    case '#':
                        is_comment = 1;
                        break;
                    case '"':
                        is_quote = 1;
                        break;
                    default:
                        break;
                    }
                } else {
                    break;
                }
            }
            i++;
        }
        if (is_test) {
            is_comment = 0;
        } else if (is_quote) {
            break;
        }
    }
    new_config.content[i] = '\0';
    new_config.start_pos += i;
    return new_config;
}