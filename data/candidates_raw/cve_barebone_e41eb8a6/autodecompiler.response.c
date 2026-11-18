static int
decode_snmp_message (u_char * oid, size_t oidlen,
       char **group_name, size_t * group_name_len,
       char **context_prefix, size_t * context_prefix_len,
       u_int * msg_id, u_int * msg_max_size)
{
  int i;
  int ret;
  int group_name_l, context_prefix_l;

  if (oidlen <= 0 || oid == NULL)
    {
      ret = 1;
      goto out;
    }

  group_name_l = oid[0];
  context_prefix_l = oid[group_name_l + 1];

  if (oidlen != 4 + group_name_l + context_prefix_l)
    {
      ret = 1;
      goto out;
    }

  if (context_prefix == NULL || group_name == NULL)
    {
      ret = 1;
      goto out;
    }

  *group_name = (char *) malloc (group_name_l + 1);
  if (*group_name == NULL)
    {
      ret = 1;
      goto out;
    }
  *context_prefix = (char *) malloc (context_prefix_l + 1);
  if (*context_prefix == NULL)
    {
      free (*group_name);
      ret = 1;
      goto out;
    }

  *context_prefix_len = context_prefix_l;
  *group_name_len = group_name_l;

  for (i = 0; ; i++)
    {
      if (i >= group_name_l)
 break;
      if (oid[i + 1] > 255)
 {
   free (*group_name);
   free (*context_prefix);
   ret = 1;
   goto out;
 }
      (*group_name)[i] = oid[i + 1];
    }
  (*group_name)[group_name_l] = '\0';

  for (i = 0; ; i++)
    {
      if (i >= context_prefix_l)
 break;
      if (oid[i + group_name_l + 2] > 255)
 {
   free (*group_name);
   free (*context_prefix);
   ret = 1;
   goto out;
 }
      (*context_prefix)[i] = oid[i + group_name_l + 2];
    }
  (*context_prefix)[context_prefix_l] = '\0';

  *msg_id = oid[2 + group_name_l + context_prefix_l];
  *msg_max_size = oid[3 + group_name_l + context_prefix_l];

  ret = 0;

out:
  return ret;
}