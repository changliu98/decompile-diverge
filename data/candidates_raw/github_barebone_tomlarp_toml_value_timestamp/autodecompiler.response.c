int toml_value_timestamp(struct toml_node *node, struct dt *dt)
{
 char *p;
 int ret;

 if (!node)
  return -1;

 p = node->u.time;

 memset(dt, 0, sizeof(*dt));

 if (scan_date(p, &dt->y, &dt->m, &dt->d) & 1) {
  if (dt->m < 1 || dt->d < 1 || dt->m > 12 || dt->d > 31) {
   ret = -1;
   goto out;
  }
  if (dt->m == 2 && dt->d > (is_leap(dt->y) ? 29 : 28)) {
   ret = -1;
   goto out;
  }
  dt->type = 'D';
  p += 10;
  if (*p) {
   if (*p != 'T' && *p != 't' && *p != ' ') {
    ret = -1;
    goto out;
   }
   p++;
  }
 } else {
  if (scan_time(p, &dt->h, &dt->mm, &dt->ss) & 1) {
   if (dt->mm < 0 || dt->h < 0 || dt->h > 23 || dt->mm > 59 || dt->ss > 60) {
    ret = -1;
    goto out;
   }
   p += dt->ss == -1 ? 5 : 8;
   dt->type = dt->type == 'D' ? 'l' : 't';
   if (dt->ss == -1)
    dt->ss = 0;
   if (*p == '.') {
    char *end;
    p++;
    dt->ms = parse_millisec(p, &end);
    p = end;
   }
   if (*p) {
    dt->type = 'd';
    if (*p == 'Z' || *p == 'z') {
     p++;
    } else if (*p == '+' || *p == '-') {
     if (!(scan_offset(p, &dt->tz) & 1)) {
      ret = -1;
      goto out;
     }
     p += 6;
    }
   }
  } else {
   if (*p) {
    ret = -1;
    goto out;
   }
  }
  if (must_parse_time && dt->type == 'D') {
   ret = -1;
   goto out;
  }
 }
 ret = 0;
out:
 return ret;
}