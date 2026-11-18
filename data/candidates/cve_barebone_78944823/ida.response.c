int __cdecl sample_conv_regsub(const arg *arg_p, sample *smp, void *a3)
{
  char v3; // dl
  char *area; // rax
  size_t data; // rcx
  int found; // [rsp+4h] [rbp-9Ch]
  int max; // [rsp+8h] [rbp-98h]
  int maxa; // [rsp+8h] [rbp-98h]
  int flag; // [rsp+Ch] [rbp-94h]
  buffer *output; // [rsp+10h] [rbp-90h]
  buffer *trash; // [rsp+18h] [rbp-88h]
  regmatch_t pmatch[10]; // [rsp+20h] [rbp-80h] BYREF
  my_regex *reg; // [rsp+70h] [rbp-30h]
  char *end; // [rsp+78h] [rbp-28h]
  char *start; // [rsp+80h] [rbp-20h]
  void *privatea; // [rsp+88h] [rbp-18h]
  sample *smpa; // [rsp+90h] [rbp-10h]
  const arg *v19; // [rsp+98h] [rbp-8h]

  v19 = arg_p;
  smpa = smp;
  privatea = a3;
  reg = arg_p->data.reg;
  trash = get_trash_chunk();
  start = smp->data.u.str.area;
  end = &start[smp->data.u.str.data];
  for ( flag = 0; ; flag |= 1u )
  {
    found = 0;
    if ( (v19->type_flags & 2) != 0 || (flag & 1) == 0 )
      found = regex_exec_match2(reg, start, (_DWORD)end - (_DWORD)start, 0xAuLL, pmatch, flag);
    if ( !found )
      pmatch[0].rm_so = (_DWORD)end - (_DWORD)start;
    max = LODWORD(trash->size) - LODWORD(trash->data);
    if ( max && pmatch[0].rm_so > 0 )
    {
      if ( max > pmatch[0].rm_so )
        max = pmatch[0].rm_so;
      memcpy(&trash->area[trash->data], start, max);
      trash->data += max;
    }
    if ( !found )
      break;
    output = alloc_trash_chunk();
    if ( !output )
      break;
    output->data = exp_replace(output->area, output->size, start, v19[1].data.str.area, pmatch);
    maxa = LODWORD(output->size) - LODWORD(output->data);
    if ( maxa )
    {
      if ( maxa > output->data )
        maxa = output->data;
      memcpy(&trash->area[trash->data], output->area, maxa);
      trash->data += maxa;
    }
    free_trash_chunk(output);
    if ( start >= end )
      break;
    if ( !pmatch[0].rm_eo )
    {
      if ( trash->data < trash->size )
      {
        v3 = start[pmatch[0].rm_eo];
        area = trash->area;
        data = trash->data;
        trash->data = data + 1;
        area[data] = v3;
      }
      ++pmatch[0].rm_eo;
    }
    start += pmatch[0].rm_eo;
  }
  smpa->data.u = (sample_value)*trash;
  return 1;
}