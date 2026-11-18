char get_item_type(struct menu_t *m, char *name, struct menu_entry_t **e,
  struct menu_subentry_t **se, struct menu_separator_t **sp)
{
 int i;
 char type;

 if (!sp) sp = &dummy_sp;
 if (!se) se = &dummy_se;
 if (!e) e = &dummy_e;

 *sp = NULL;
 *se = NULL;
 *e = NULL;

 for (i = 0; i < m->num_entries; i++)
 {
  if (!strcmp(name, m->entries[i]->text))
  {
   *e = m->entries[i];
   type = 'v';
   goto found;
  }
 }

 for (i = 0; i < m->num_subentries; i++)
 {
  if (!strcmp(name, m->subentries[i]->text))
  {
   *se = m->subentries[i];
   type = 'a';
   goto found;
  }
 }

 for (i = 0; i < m->num_separators; i++)
 {
  if (!strcmp(name, m->separators[i]->text))
  {
   *sp = m->separators[i];
   type = 't';
   goto found;
  }
 }

 type = 0;

found:
 return type;
}