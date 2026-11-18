static void add_element_to_tree(struct element *e)
{
 int i, j, k, c = -1;
 struct element *ne;
 char buf[200];
 struct element_attrib *ea;
 struct element_attrib *ea2;

 j = 0;
 k = supported_elements_count;
 while (1) {
  if (k <= j)
   break;
  i = (k + j) / 2;
  c = strcmp(&e->name[8], supported_elements[i].name);
  if (c == 0)
   break;
  else if (c < 0)
   k = i;
  else
   j = i + 1;
 }
 if (c != 0) {

  ne = tree_search(&unknown_element_tree, &e->name[8]);
  if (!ne) {
   ne = (struct element *)misc_malloc(sizeof(*ne) + strlen(&e->name[8]));
   strcpy(&ne->name[8], &e->name[8]);
   tree_insertnode(&unknown_element_tree, ne);
  }
  return;
 }

 ea = e->attribs;
 while (ea) {
  if ((strncmp(&ea->name[8], "#", 1) == 0) ||
      (strcmp(&ea->name[8], "revisionflag") == 0 &&
       strcmp(&ea->value[8], "changed") == 0)) {
   ea = ea->next;
   continue;
  }
  if (ea->values) {
   for (ea2 = ea->values; ea2->name; ea2++) {
    if (strcmp(ea2->name, &ea->name[8]) == 0)
     break;
   }
   if (ea2->name)
    ea = ea->next;
   else
    sprintf(buf, "+%s=%s:%s", &ea->name[8], &ea->value[8],
     &e->name[8]);
  } else
   sprintf(buf, "+%s:%s", &ea->name[8], &e->name[8]);

  ne = tree_search(&unknown_element_tree, buf);
  if (!ne) {
   ne = (struct element *)misc_malloc(sizeof(*ne) + strlen(buf));
   strcpy(&ne->name[8], buf);
   tree_insertnode(&unknown_element_tree, ne);
  }
  ea = ea->next;
 }
}