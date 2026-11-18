cJSON * get_object_item(cJSON *object,char *name,cJSON_bool case_sensitive)

{
  int iVar1;
  bool bVar2;
  cJSON *current_element;
  cJSON_bool case_sensitive_local;
  char *name_local;
  cJSON *object_local;
  cJSON *local_10;
  
  if ((object == (cJSON *)0x0) || (name == (char *)0x0)) {
    local_10 = (cJSON *)0x0;
  }
  else {
    current_element = object->child;
    if (case_sensitive == 0) {
      while( true ) {
        bVar2 = false;
        if (current_element != (cJSON *)0x0) {
          iVar1 = case_insensitive_strcmp((uchar *)name,(uchar *)current_element->string);
          bVar2 = iVar1 != 0;
        }
        if (!bVar2) break;
        current_element = current_element->next;
      }
    }
    else {
      while( true ) {
        bVar2 = false;
        if (current_element != (cJSON *)0x0) {
          iVar1 = strcmp(name,current_element->string);
          bVar2 = iVar1 != 0;
        }
        if (!bVar2) break;
        current_element = current_element->next;
      }
    }
    local_10 = current_element;
  }
  return local_10;
}