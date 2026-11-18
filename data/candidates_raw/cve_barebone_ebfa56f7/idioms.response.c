void add_to_known_elements(struct item *item)
{
  char buffer[-1];
  struct item *i = item;
  int c = -1;
  int bot = 0; int top = supported_elements_count;
  while (top > bot) {
    int mid = (bot + top)/2;
    c = strncmp(i->name, supported_elements[mid], 255);
    if (c == 0) break;
    if (c < 0) {
      top = mid;
    } else {
      bot = mid + 1;
    }
  }
  if (c == 0) {
    struct paramstr *p = i->p.param;
    while (p != ((void *)0)) {
      if (p->name[0] == '#') {
        p = p->next;
        continue;
      }
      if (strncmp(p->name, "revisionflag", 255) == 0) {
        if (strncmp(p->value, "changed", 255) == 0) {
          str_printf(buffer, "+%s=%s:%s", p->name, p->value, i->name);
        }
      } else {
        char **list = supported_elements[mid + 1];
        if (list == ((void *)0)) {
          str_printf(buffer, "+%s:%s", p->name, i->name);
        } else if (strncmp(*list, "*", 255) == 0) {
          while (*list != ((void *)0) && strncmp(*list, p->name, 255) != 0) {
            list++;
          }
          if (*list != ((void *)0)) {
          } else {
            str_printf(buffer, "+%s:%s", p->name, i->name);
          }
        } else {
          str_printf(buffer, "+%s=%s:%s", p->name, p->value, i->name);
        }
      }
      struct tree_node *n = find_in_tree(unknown_element_tree, buffer);
      if (n == ((void *)0)) {
        n = tree_get_node(sizeof(struct tree_node) + strlen(buffer));
        strcpy(n->name, buffer);
        tree_add_node(unknown_element_tree, n);
      }
      p = p->next;
    }
  } else {
    struct tree_node *n = find_in_tree(unknown_element_tree, i->name);
    if (n == ((void *)0)) {
      n = tree_get_node(sizeof(struct tree_node) + strlen(i->name));
      strcpy(n->name, i->name);
      tree_add_node(unknown_element_tree, n);
    }
  }
}