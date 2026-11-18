static plist_t parse_string_node(plist_t node, size_t len)
{
 plist_data_t *data = _plist_new_plist_data();
 data->type = 3;
 data->value = (char *)malloc((len + 1) * sizeof(char));
 memcpy(data->value, node->data.value, len);
 ((char *)data->value)[len] = '\0';
 data->count = (uint32_t)strlen((char *)data->value);
 return node_create(NULL, data);
}