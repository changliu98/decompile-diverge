plist_t parse_string_node(char **bnode,uint64_t size)

{
  plist_data_t data_00;
  void *pvVar1;
  size_t sVar2;
  node_t *pnVar3;
  plist_data_t data;
  uint64_t size_local;
  char **bnode_local;
  
  data_00 = plist_new_plist_data();
  data_00->type = PLIST_STRING;
  pvVar1 = malloc(size + 1);
  (data_00->field_0).hashtable = pvVar1;
  memcpy((data_00->field_0).hashtable,*bnode,size);
  (data_00->field_0).strval[size] = '\0';
  sVar2 = strlen((data_00->field_0).strval);
  data_00->length = sVar2;
  pnVar3 = node_create((node_t *)0x0,data_00);
  return pnVar3;
}