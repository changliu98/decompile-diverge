void cJSON_Minify(char *json)
{
  char *in = json;
  char *out = json;
  int c;
  if (in) {
    while (*in) {
      c = *in;
      if (c < ' ' || c == '\r' || c == ' ') {
        in++;
      }
      else if (c == '"') {
        json_string(&in, &out);
      }
      else if (c == '/') {
        if (in[1] == '/') {
          json_line(&in);
        }
        else if (in[1] == '*') {
          json_block(&in);
        }
        else {
          in++;
        }
      }
      else {
        *out = *in;
        in++;
        out++;
      }
    }
    *out = '\0';
  }
}