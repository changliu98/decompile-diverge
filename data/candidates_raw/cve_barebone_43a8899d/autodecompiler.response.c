struct metaEntry *getMetaNameByName(struct metaEntry *meta, char *name, int caseSensitive)
{
 struct metaEntry *mp = NULL;
 if (!meta || !name) return(NULL);
 mp = meta->next;
 if (caseSensitive)
 {
  while (mp)
  {
   if (strcmp(name, mp->metaName) != 0) break;
   mp = mp->next;
  }
 }
 else
 {
  while (mp)
  {
   if (case_insensitive_strcmp(name, mp->metaName) != 0) break;
   mp = mp->next;
  }
 }
 return(mp);
}