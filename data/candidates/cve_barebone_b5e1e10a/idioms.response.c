void print_udta(struct _GF_ISOFile *iso, unsigned int track, _Bool has_itags)
{
  unsigned int count = get_itags_count(iso, track);
  if (count == 0)
    return;
  if (has_itags == GF_FALSE)
    goto print_itags_end;
  for (unsigned int i = 0; i < count; i++)
  {
    unsigned int type;
    struct _bin128 uuid;
    get_itags(iso, track, i + 1, &type, &uuid);
    if (type == 0x69000101)
    {
      count--;
      break;
    }
  }
  if (count == 0)
    return;
print_itags_end:
  print_to(stderr, "%d UDTA types: ", count);
  for (unsigned int i = 0; i < count; i++)
  {
    unsigned int type;
    struct _bin128 uuid;
    unsigned int items = get_itags_count_type(iso, track, type, uuid);
    print_to(stderr, "%s (%d) ", get_itags_type_name(type), items);
    for (unsigned int j = 0; j < items; j++)
    {
      char *udta = ((void *)0);
      unsigned int udta_size = 0;
      get_itags_udta(iso, track, type, uuid, j + 1, &udta, &udta_size);
      if (udta == ((void *)0))
        continue;
      if (is_itags_udta_text(udta, udta_size))
      {
        unsigned int first = 1;
        if (first)
        {
          print_to(stderr, "\n");
          first = 0;
        }
        print_to(stderr, "\t%s\n", udta);
      }
      free(udta);
    }
  }
  print_to(stderr, "\n");
}