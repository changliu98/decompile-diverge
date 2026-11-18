void check_supported(item *new)
{
  int i, c;
  int bot, top, mid;
  paramstr *p;
  tree_node *tn;
  char **ap;
  char *cp;
  char buff[256];

  bot = 0;
  top = supported_elements_count;
  c = -1;
  while (bot < top) {
    mid = (bot + top) / 2;
    c = strcmp(new->name, supported_elements[mid].name);
    if (c == 0) break;
    if (c < 0) top = mid; else bot = mid + 1;
  }
  if (c != 0) {
    tn = tree_search(unknown_element_tree, new->name);
    if (tn == NULL) {
      tn = (tree_node *)misc_malloc(sizeof(tree_node) + strlen(new->name));
      strcpy(tn->name, new->name);
      tree_insertnode(&unknown_element_tree, tn);
    }
    return;
  }

  for (p = new->p.param; p != NULL; p = p->next) {
    if (p->name[0] == '#') continue;
    if (!strcmp(p->name, "revisionflag") && !strcmp(p->value, "changed")) continue;
    ap = supported_elements[mid].attrs;
    if (ap == NULL || !strcmp(*ap, "*")) {
      sprintf(buff, "+%s:%s", p->name, new->name);
      tn = tree_search(unknown_element_tree, buff);
      if (tn == NULL) {
        tn = (tree_node *)misc_malloc(sizeof(tree_node) + strlen(buff));
        strcpy(tn->name, buff);
        tree_insertnode(&unknown_element_tree, tn);
      }
      continue;
    }
    while (*ap != NULL && strcmp(*ap, p->name)) ap++;
    if (*ap == NULL) {
      sprintf(buff, "+%s:%s", p->name, new->name);
      tn = tree_search(unknown_element_tree, buff);
      if (tn == NULL) {
        tn = (tree_node *)misc_malloc(sizeof(tree_node) + strlen(buff));
        strcpy(tn->name, buff);
        tree_insertnode(&unknown_element_tree, tn);
      }
      continue;
    }
  }
}