struct plist *plist_new_string(char *str, unsigned long len)
{
  struct plist_data *data = plist_new_plist_data();
  data->type = PLIST_STRING;
  data->intval = plist_new_string_val(len + 1);
  plist_set(data->hashtable, str, len);
  data->intval[len] = '\0';
  data->length = plist_string_length(data->strval);
  return plist_new(PLIST_PLIST, data);
}