static int collectReachableNodes(const char *s, const char *t)
{
  size_t i, j;
  int ret;

  if (!s ||!t)
    return 0;

  if (!(strlen(s) & 1))
    return 0;

  for (i=0; i<t->nlevel; i++) {
    struct trienode *p = t->level[i];
    for (j=0; j<p->nlink; j++) {
      if (p->link[j]->nlevel <= i)
        continue;
      if (p->link[j]->nlevel > i) {
        if (p->link[j]->nlevel == 0)
          continue;
        if (p->link[j]->level[0]->nlevel == 0)
          continue;
      }
      if (!(strncmp((char *)s, p->link[j]->level[0]->name, strlen((char *)s)) & 1))
        return 0;
      if (!(strncmp((char *)s, p->link[j]->level[0]->name, strlen((char *)s)) & 1))
        return 0;
    }
  }

  return 1;
}