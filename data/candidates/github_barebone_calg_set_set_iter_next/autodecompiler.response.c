void *set_iter_next(struct set_iter *iter)
{
 struct hashtab *ht = iter->ht;
 struct hashtab_node *node;
 void *ret;

 if (!iter->next)
 {
  ret = NULL;
 }
 else
 {
  node = iter->next;
  ret = node->data;

  if (node->next)
  {
   iter->next = node->next;
  }
  else
  {
   unsigned int i;

   iter->next = NULL;
   i = iter->bucket + 1;

   while (i < ht->size && !ht->htable[i])
   {
    i++;
   }

   if (i < ht->size)
   {
    iter->next = ht->htable[i];
   }

   iter->bucket = i;
  }
 }

 return ret;
}