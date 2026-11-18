void check_supported(def_t *def) {
  int cmp = -1;
  int low = 0;
  int high = num_supported;
  int mid;
  attr_t *attr;
  tree_node_t *node;
  char buf[256];
  string_t *str;
  char **p;
  while (high > low) {
    mid = (low + high) / 2;
    cmp = strcmp(def->name, supported[mid].name);
    if (cmp == 0) break;
    if (cmp < 0)
      high = mid;
    else
      low = mid + 1;
  }
  if (cmp == 0) {
    attr = def->attrs.head;
    while (attr != NULL) {
      if (attr->name[0] == '#') {
      } else if (!strcmp(attr->name, "revisionflag")) {
        if (!strcmp(attr->value, "changed")) {
        } else {
          sprintf(buf, "+%s=%s:%s", attr->name, attr->value, def->name);
          str = tree_search(supported_list, buf);
          if (str == NULL) {
            str = misc_malloc(strlen(buf) + 32);
            strcpy(str->name, buf);
            tree_insertnode(&supported_list, str);
          }
        }
      } else {
        p = supported[mid].attrs;
        if (p == NULL) {
          sprintf(buf, "+%s:%s", attr->name, def->name);
          str = tree_search(supported_list, buf);
          if (str == NULL) {
            str = misc_malloc(strlen(buf) + 32);
            strcpy(str->name, buf);
            tree_insertnode(&supported_list, str);
          }
        } else {
          if (!strcmp(*p, "*")) {
          } else {
            while (*p != NULL && strcmp(*p, attr->name)) p++;
            if (*p == NULL) {
              sprintf(buf, "+%s:%s", attr->name, def->name);
              str = tree_search(supported_list, buf);
              if (str == NULL) {
                str = misc_malloc(strlen(buf) + 32);
                strcpy(str->name, buf);
                tree_insertnode(&supported_list, str);
              }
            }
          }
        }
      }
      attr = attr->next;
    }
  }
  node = tree_search(supported_list, def->name);
  if (node == NULL) {
    str = misc_malloc(strlen(def->name) + 32);
    strcpy(str->name, def->name);
    tree_insertnode(&supported_list, str);
  }
}