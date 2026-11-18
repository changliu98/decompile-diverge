int __cdecl parse_device(dev_t *pdev, archive *a, char *val)
{
  char *v3; // rax
  int64_t v4; // rcx
  int v5; // eax
  const char *error; // [rsp+0h] [rbp-70h] BYREF
  dev_t result; // [rsp+8h] [rbp-68h]
  pack_t *pack; // [rsp+10h] [rbp-60h]
  int argc; // [rsp+1Ch] [rbp-54h]
  char *dev; // [rsp+20h] [rbp-50h] BYREF
  char *p; // [rsp+28h] [rbp-48h] BYREF
  unsigned __int64 numbers[3]; // [rsp+30h] [rbp-40h] BYREF
  char *vala; // [rsp+50h] [rbp-20h] BYREF
  archive *aa; // [rsp+58h] [rbp-18h]
  dev_t *pdeva; // [rsp+60h] [rbp-10h]

  pdeva = pdev;
  aa = a;
  vala = val;
  error = 0LL;
  memset(pdev, 0, sizeof(dev_t));
  dev = strchr(vala, 44);
  if ( !dev )
  {
    result = mtree_atol(&vala);
    goto LABEL_17;
  }
  v3 = dev++;
  *v3 = 0;
  pack = pack_find(vala);
  if ( pack )
  {
    argc = 0;
    while ( 1 )
    {
      p = la_strsep(&dev, ",");
      if ( !p )
        break;
      if ( !*p )
      {
        archive_set_error(aa, 22, "Missing number");
        return -20;
      }
      v4 = mtree_atol(&p);
      v5 = argc++;
      numbers[v5] = v4;
      if ( argc > 3 )
      {
        archive_set_error(aa, 22, "Too many arguments");
        return -20;
      }
    }
    if ( argc < 2 )
    {
      archive_set_error(aa, 22, "Not enough arguments");
      return -20;
    }
    result = pack(argc, numbers, &error);
    if ( error )
    {
      archive_set_error(aa, 22, "%s", error);
      return -20;
    }
LABEL_17:
    *pdeva = result;
    return 0;
  }
  archive_set_error(aa, 22, "Unknown format `%s'", vala);
  return -20;
}