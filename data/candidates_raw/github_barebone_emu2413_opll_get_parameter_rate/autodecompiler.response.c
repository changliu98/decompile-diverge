int
get_sfx_priority(struct sfx_t *sfx)
{
 int priority;
 if ((((sfx->flags & 0x0100) == 0) && ((sfx->priority) == 0)))
 {
  priority = 0;
 }
 else
 {
  int p = sfx->type;
  switch(p)
  {
  case 0:
   priority = sfx->data[4];
   break;
  case 1:
   priority = sfx->data[5];
   break;
  case 2:
  {
   int p = sfx->data[2] ? 0 : sfx->data[7];
   priority = p;
   break;
  }
  case 3:
  {
   if (sfx->priority)
   {
    priority = 5;
   }
   else
   {
    if (sfx->data[2])
    {
     priority = sfx->data[7];
    }
    else
    {
     priority = 7;
    }
   }
   break;
  }
  case 4:
   priority = 12;
   break;
  default:
   priority = 0;
  }
 }
 return priority;
}