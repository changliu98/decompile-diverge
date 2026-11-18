struct tl_act_extra *r_bin_java_inner_classes_attr_new(char *name, char *args, size_t args_len,
                                         char *args_buf) {
  struct tl_act_extra *extra = NULL;
  int i = 0;
  struct tl_combinator *c = NULL;
  struct tl_combinator *c2 = NULL;
  while (1) {
    c = tl_combinator_find_by_name (name, args, args_len, args_buf);
    if (!c) {
      c = c2;
      break;
    }
    c->ref_cnt ++;
    c->flags = 0x7;
    c->args_len = (args[i] & 0xff) | ((args[i + 1] & 0xff) << 8);
    i += 2;
    c->args_buf = args_buf + i;
    if (i + 2 > args_len) {
      c2 = c;
      break;
    }
    c2 = zmalloc0 (sizeof (*c2));
    if (!c2) {
      break;
    }
    memcpy (c2->name, c->name, c->name_len);
    c2->name_len = c->name_len;
    c2->flags = c->flags;
    c2->ref_cnt = 0;
    c2->next = c2;
    c2->args_len = c->args_len;
    c2->args_buf = c->args_buf;
  }
  extra = tl_act_extra_init (&tl_list_type);
  extra->extra = c;
  return extra;
}