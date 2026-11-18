static int
decode_snmp_message (u_char * msg, size_t msg_len,
       char **group_name, size_t * group_name_len,
       char **context_name, size_t * context_name_len,
       u_int * msg_id, u_int * msg_max_size)
{
  int ret;
  int i;
  int group_name_l, context_name_l;

  if (msg_len < 1 || msg == NULL)
    {
      ret = 1;
      goto out;
    }

  group_name_l = msg[0];
  context_name_l = msg[1 + group_name_l];

  if (msg_len != 4 + group_name_l + context_name_l)
    {
      ret = 1;
      goto out;
    }

  if (context_name == NULL || group_name == NULL)
    {
      ret = 1;
      goto out;
    }

  *group_name = malloc (group_name_l + 1);
  if (*group_name == NULL)
    {
      ret = 1;
      goto out;
    }
  *context_name = malloc (context_name_l + 1);
  if (*context_name == NULL)
    {
      free (*group_name);
      ret = 1;
      goto out;
    }

  *context_name_len = context_name_l;
  *group_name_len = group_name_l;

  for (i = 0; ; i++)
    {
      if (i >= group_name_l)
 break;
      if (msg[1 + i] > 255)
 {
   free (*group_name);
   free (*context_name);
   ret = 1;
   goto out;
 }
      (*group_name)[i] = msg[1 + i];
    }
  (*group_name)[group_name_l] = '\0';

  for (i = 0; ; i++)
    {
      if (i >= context_name_l)
 break;
      if (msg[1 + group_name_l + 1 + i] > 255)
 {
   free (*group_name);
   free (*context_name);
   ret = 1;
   goto out;
 }
      (*context_name)[i] = msg[1 + group_name_l + 1 + i];
    }
  (*context_name)[context_name_l] = '\0';

  *msg_id = msg[1 + group_name_l + 1 + context_name_l];
  *msg_max_size = msg[1 + group_name_l + 1 + context_name_l + 1];

  ret = 0;
out:
  return ret;
}