void check_supported(item *new)

{
  int iVar1;
  tree_node *ptVar2;
  size_t sVar3;
  uschar **aptr;
  uschar buffer [256];
  paramstr *param;
  tree_node *tn;
  int mid;
  int top;
  int bot;
  int c;
  item *new_local;
  
  c = -1;
  bot = 0;
  top = supported_elements_count;
  iVar1 = top;
  while (top = iVar1, bot < top) {
    mid = (top + bot) / 2;
    c = strcmp((char *)new->name,(char *)supported_elements[mid].name);
    if (c == 0) break;
    iVar1 = mid;
    if (-1 < c) {
      bot = mid + 1;
      iVar1 = top;
    }
  }
  if (c == 0) {
    for (param = (new->p).param; param != (paramstr *)0x0; param = param->next) {
      if (param->name[0] != '#') {
        iVar1 = strcmp((char *)param->name,"revisionflag");
        if (iVar1 == 0) {
          iVar1 = strcmp((char *)param->value,"changed");
          if (iVar1 != 0) {
            sprintf((char *)buffer,"+%s=%s:%s",param->name,param->value,new->name);
LAB_00102b73:
            ptVar2 = tree_search(unknown_element_tree,buffer);
            if (ptVar2 == (tree_node *)0x0) {
              sVar3 = strlen((char *)buffer);
              ptVar2 = misc_malloc((int)sVar3 + 0x20);
              strcpy((char *)ptVar2->name,(char *)buffer);
              tree_insertnode(&unknown_element_tree,ptVar2);
            }
          }
        }
        else {
          aptr = supported_elements[mid].attrs;
          if (aptr == (uschar **)0x0) {
LAB_00102b4e:
            sprintf((char *)buffer,"+%s:%s",param->name,new->name);
            goto LAB_00102b73;
          }
          iVar1 = strcmp((char *)*aptr,"*");
          if (iVar1 != 0) {
            while ((*aptr != (uschar *)0x0 &&
                   (iVar1 = strcmp((char *)*aptr,(char *)param->name), iVar1 != 0))) {
              aptr = aptr + 1;
            }
            if (*aptr == (uschar *)0x0) goto LAB_00102b4e;
          }
        }
      }
    }
  }
  else {
    ptVar2 = tree_search(unknown_element_tree,new->name);
    if (ptVar2 == (tree_node *)0x0) {
      sVar3 = strlen((char *)new->name);
      ptVar2 = misc_malloc((int)sVar3 + 0x20);
      strcpy((char *)ptVar2->name,(char *)new->name);
      tree_insertnode(&unknown_element_tree,ptVar2);
    }
  }
  return;
}