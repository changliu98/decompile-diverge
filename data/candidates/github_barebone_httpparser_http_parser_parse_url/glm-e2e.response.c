int http_parser_parse_url(const char *buf, unsigned long len, int is_connect, struct http_parser_url *u) {
    int found_at = 0;
    int error = 1;

    if (len == 0) {
        return 1;
    }

    u->field_set = 0;
    u->port = 0;

    int state;
    if (is_connect) {
        state = 0x18; // s_req_host_start
    } else {
        state = 0x14; // s_req_spaces_before_url
    }

    int prev_state = 7; // s_dead
    const char *p = buf;
    const char *end = buf + len;

    while (p < end) {
        state = parse_url_char(state, *p);

        // Assert that state is valid (1 <= state <= 30)
        if (state - 1U > 29U) {
            assert("invalid state" && 0);
        }

        int new_state;
        switch (state) {
            case 1: // s_dead
                return 1;
            case 2: // s_req_spaces_before_url
                new_state = 0;
                break;
            case 3: // s_req_schema
            case 4: // s_req_schema_slash
            case 5: // s_req_schema_slash_slash
            case 6: // s_req_server_start
                new_state = state - 2;
                break;
            case 7: // s_req_host
                found_at = 1;
                new_state = 1;
                break;
            case 8: // s_req_path
                new_state = 3;
                break;
            case 9: // s_req_query_string_start
            case 10: // s_req_query_string
                new_state = 4;
                break;
            case 11: // s_req_fragment_start
            case 12: // s_req_fragment
                new_state = 5;
                break;
            default:
                new_state = 0;
                break;
        }

        if (new_state != prev_state) {
            u->field_data[new_state].len = (unsigned short)(p - buf);
            u->field_data[new_state].off = 1;
            u->field_set |= (1 << new_state);
            prev_state = new_state;
        } else {
            u->field_data[new_state].len++;
        }
        p++;
    }

    // Host validation
    if ((u->field_set & 1) && !(u->field_set & 2)) {
        return 1;
    }

    if (u->field_set & 2) {
        if (http_parse_host(buf, u, found_at) != 0) {
            return 1;
        }
    }

    // Connect request validation
    if (is_connect) {
        if (u->field_set != 6) { // Must have exactly HOST and PORT
            return 1;
        }
    } else {
        if (u->field_set & 4) { // If PATH is set
            unsigned short off = u->field_data[3].off;
            unsigned short len_field = u->field_data[3].len;
            const char *p_end = buf + off + len_field;

            // Assert that off + len_field <= len
            assert(off + len_field <= len);

            unsigned long port_val = 0;
            const char *p_port = buf + off;
            while (p_port < p_end) {
                port_val = port_val * 10 + (*p_port - '0');
                if (port_val > 0xffff) {
                    return 1;
                }
                p_port++;
            }
            u->port = (unsigned short)port_val;
        }
    }

    error = 0;
    return error;
}