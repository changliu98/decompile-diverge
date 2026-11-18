int xrdp_wm_parse_domain_information(char* data, int max_domain, int use_index,
                                     char* domain) {
  int index = 0;
  int pos;
  int i;
  char tmp[2];
  memset(domain, 0, 256);
  if (data[0] == '_') {
    pos = g_pos(data + 1, "__");
    if (pos > 0) {
      if (use_index) {
        memset(tmp, 0, 2);
        g_strncpy(tmp, data + pos + 3, 1);
        i = g_htoi(tmp);
        if ((i > 0) && (i < max_domain)) {
          index = i;
        }
      }
      g_strncpy(domain, data + 1, pos);
    } else {
      g_strncpy(domain, data + 1, 255);
    }
  }
  return index;
}