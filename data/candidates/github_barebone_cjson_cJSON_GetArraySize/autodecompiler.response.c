int cJSON_GetArraySize(cJSON *array)
{
 int len;
 struct node *p = NULL;
 size_t i = 0;

 if (array == NULL) {
  len = 0;
 } else {
  p = array->child;
  while (1) {
   if (p == NULL)
    break;
   ++i;
   p = p->next;
  }
  len = i;
 }

 return len;
}