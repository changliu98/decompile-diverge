void __cdecl check_supported(item *a1)
{
  int v1; // eax
  int v2; // eax
  const char **aptr; // [rsp+8h] [rbp-138h]
  uschar buffer[256]; // [rsp+10h] [rbp-130h] BYREF
  paramstr *param; // [rsp+118h] [rbp-28h]
  tree_node *tn; // [rsp+120h] [rbp-20h]
  int mid; // [rsp+128h] [rbp-18h]
  int top; // [rsp+12Ch] [rbp-14h]
  int bot; // [rsp+130h] [rbp-10h]
  int c; // [rsp+134h] [rbp-Ch]
  item *newa; // [rsp+138h] [rbp-8h]

  newa = a1;
  c = -1;
  bot = 0;
  top = supported_elements_count;
  while ( top > bot )
  {
    mid = (bot + top) / 2;
    c = strcmp((const char *)newa->name, (&supported_elements)[2 * mid]);
    if ( !c )
      break;
    if ( c >= 0 )
      bot = mid + 1;
    else
      top = mid;
  }
  if ( !c )
  {
    for ( param = newa->p.param; ; param = param->next )
    {
      if ( !param )
        return;
      if ( param->name[0] != 35 )
      {
        if ( !strcmp((const char *)param->name, "revisionflag") )
        {
          if ( !strcmp((const char *)param->value, "changed") )
            continue;
          sprintf(
            (char *)buffer,
            "+%s=%s:%s",
            (const char *)param->name,
            (const char *)param->value,
            (const char *)newa->name);
          goto LABEL_24;
        }
        aptr = (const char **)(&supported_elements)[2 * mid + 1];
        if ( !aptr )
          goto LABEL_23;
        if ( strcmp(*aptr, "*") )
        {
          while ( *aptr && strcmp(*aptr, (const char *)param->name) )
            ++aptr;
          if ( !*aptr )
          {
LABEL_23:
            sprintf((char *)buffer, "+%s:%s", (const char *)param->name, (const char *)newa->name);
LABEL_24:
            tn = tree_search(unknown_element_tree, buffer);
            if ( !tn )
            {
              v2 = strlen((const char *)buffer);
              tn = (tree_node *)misc_malloc(v2 + 32);
              strcpy((char *)tn->name, (const char *)buffer);
              tree_insertnode(&unknown_element_tree, tn);
            }
            continue;
          }
        }
      }
    }
  }
  if ( !tree_search(unknown_element_tree, newa->name) )
  {
    v1 = strlen((const char *)newa->name);
    tn = (tree_node *)misc_malloc(v1 + 32);
    strcpy((char *)tn->name, (const char *)newa->name);
    tree_insertnode(&unknown_element_tree, tn);
  }
}