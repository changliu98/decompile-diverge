char *__cdecl base_name(const char *name)
{
  size_t v1; // rax
  char *p; // [rsp+8h] [rbp-28h]
  idx_t length; // [rsp+18h] [rbp-18h]
  const char *base; // [rsp+20h] [rbp-10h]

  base = last_component(name);
  if ( *base )
  {
    v1 = base_len(base);
    length = v1 + (base[v1] == 47);
  }
  else
  {
    base = name;
    length = base_len(name);
  }
  p = (char *)ximalloc(length + 1);
  memcpy(p, base, length);
  p[length] = 0;
  return p;
}