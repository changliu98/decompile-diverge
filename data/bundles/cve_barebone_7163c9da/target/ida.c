plist_t __cdecl parse_string_node(const char **bnode, uint64_t size)
{
  plist_data_t data; // [rsp+8h] [rbp-18h]

  data = plist_new_plist_data();
  data->type = PLIST_STRING;
  data->intval = (uint64_t)malloc(size + 1);
  memcpy(data->hashtable, *bnode, size);
  *(_BYTE *)(data->intval + size) = 0;
  data->length = strlen(data->strval);
  return node_create(0LL, data);
}