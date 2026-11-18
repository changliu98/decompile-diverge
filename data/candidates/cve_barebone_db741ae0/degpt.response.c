int burl_normalize_2F_to_slash_fix(buffer *b,int qs,int i)

{
  char *pcVar1;
  int iVar2;
  size_t sVar3;
  int local_30;
  int j;
  int used;
  int blen;
  char *s;
  int i_local;
  int qs_local;
  buffer *b_local;
  
  pcVar1 = b->ptr;
  sVar3 = buffer_string_length(b);
  iVar2 = (int)sVar3;
  j = i;
  i_local = i;
  local_30 = qs;
  if (qs < 0) {
    local_30 = iVar2;
  }
  for (; i_local < local_30; i_local = i_local + 1) {
    pcVar1[j] = pcVar1[i_local];
    if (((pcVar1[i_local] == '%') && (pcVar1[i_local + 1] == '2')) && (pcVar1[i_local + 2] == 'F'))
    {
      pcVar1[j] = '/';
      i_local = i_local + 2;
    }
    j = j + 1;
  }
  if (-1 < qs) {
    memmove(pcVar1 + j,pcVar1 + qs,(long)(iVar2 - qs));
    j = (iVar2 - qs) + j;
  }
  buffer_string_set_length(b,(long)j);
  return qs;
}