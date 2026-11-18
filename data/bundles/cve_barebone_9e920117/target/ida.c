njs_int_t __cdecl njs_module_path(njs_vm_t *vm, const njs_str_t *dir, njs_module_info_t *info)
{
  char *v3; // rax
  int v4; // eax
  size_t v5; // rax
  char *v7; // [rsp+0h] [rbp-1050h]
  char *v8; // [rsp+8h] [rbp-1048h]
  char src[4097]; // [rsp+10h] [rbp-1040h] BYREF
  njs_bool_t trail; // [rsp+1018h] [rbp-38h]
  size_t length; // [rsp+1020h] [rbp-30h]
  char *p; // [rsp+1028h] [rbp-28h]
  njs_module_info_t *infoa; // [rsp+1030h] [rbp-20h]
  const njs_str_t *dira; // [rsp+1038h] [rbp-18h]
  njs_vm_t *vma; // [rsp+1040h] [rbp-10h]

  vma = vm;
  dira = dir;
  infoa = info;
  trail = 0LL;
  length = info->name.length;
  if ( dir )
  {
    length = dira->length;
    if ( !length )
      return -3LL;
    trail = dira->start[dira->length - 1] != 47;
    if ( trail )
      ++length;
  }
  if ( length > 0x1000 )
    return -1LL;
  p = src;
  if ( dira )
  {
    v8 = p;
    memcpy(p, dira->start, dira->length);
    p = &v8[dira->length];
    if ( trail )
    {
      v3 = p++;
      *v3 = 47;
    }
  }
  v7 = p;
  memcpy(p, infoa->name.start, infoa->name.length);
  p = &v7[infoa->name.length];
  *p = 0;
  p = realpath(src, infoa->path);
  if ( !p )
    return -3LL;
  v4 = open(infoa->path, 0);
  infoa->fd = v4;
  if ( infoa->fd < 0 )
    return -3LL;
  infoa->file.start = (u_char *)infoa->path;
  v5 = strlen((const char *)infoa->file.start);
  infoa->file.length = v5;
  return 0LL;
}