char *gf_bt_get_next(gf_bt *in, gf_bool is_key) {
  gf_bool done = gf_false;
  int i;
  int in_string;
  gf_bt_check_line(in);
  i = 0;
  in_string = 0;
  do {
    if (in->line[in->line_pos + i] == '"') {
      in_string = !in_string;
      in->line_pos++;
      if (in->line_pos + i == in->line_len) {
        break;
      }
    }
    if (in_string) {
      in->token[i] = in->line[in->line_pos + i];
      i++;
      continue;
    }
    switch (in->line[in->line_pos + i]) {
      case '\t':
      case '\n':
      case '\r':
      case ' ':
      case ',':
      case 0:
        done = gf_true;
        break;
      case '.':
        if (is_key) {
          done = gf_true;
        }
        break;
      case '[':
      case ']':
      case '{':
      case '}':
        done = gf_true;
        break;
    }
    if (done == gf_true) {
      break;
    }
    in->token[i] = in->line[in->line_pos + i];
    i++;
  } while (in->line_pos + i != in->line_len);
  in->token[i] = 0;
  in->line_pos += i;
  return in->token;
}