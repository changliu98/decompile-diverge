node* parse_string_node(unsigned char** data, unsigned long length) {
  plist_data* pd = plist_new_plist_data();
  pd->type = PLIST_STRING;
  pd->string_value = malloc(length + 1);
  memcpy(pd->data, *data, length);
  pd->string_value[length] = '\0';
  pd->length = strlen(pd->string_value);
  return node_create(NULL, pd);
}