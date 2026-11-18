int sample_conv_regsub(arg *arg_p,sample *smp,void *private)

{
  char cVar1;
  my_regex *preg;
  size_t sVar2;
  int iVar3;
  buffer *pbVar4;
  char *pcVar5;
  buffer *chunk;
  int found;
  int max;
  int flag;
  buffer *output;
  buffer *trash;
  regmatch_t pmatch [10];
  my_regex *reg;
  char *end;
  char *start;
  void *private_local;
  sample *smp_local;
  arg *arg_p_local;
  
  preg = (arg_p->data).reg;
  pbVar4 = get_trash_chunk();
  start = (smp->data).u.str.area;
  pcVar5 = start + (smp->data).u.str.data;
  flag = 0;
  while( true ) {
    found = 0;
    iVar3 = (int)pcVar5;
    if (((arg_p->type_flags & 2) != 0) || (flag == 0)) {
      found = regex_exec_match2(preg,start,iVar3 - (int)start,10,pmatch,flag);
    }
    if (found == 0) {
      pmatch[0].rm_so = iVar3 - (int)start;
    }
    max = (int)pbVar4->size - (int)pbVar4->data;
    if ((max != 0) && (0 < pmatch[0].rm_so)) {
      if (pmatch[0].rm_so < max) {
        max = pmatch[0].rm_so;
      }
      memcpy(pbVar4->area + pbVar4->data,start,(long)max);
      pbVar4->data = (long)max + pbVar4->data;
    }
    if ((found == 0) || (chunk = alloc_trash_chunk(), chunk == (buffer *)0x0)) break;
    iVar3 = exp_replace(chunk->area,(uint)chunk->size,start,arg_p[1].data.str.area,pmatch);
    chunk->data = (long)iVar3;
    max = (int)chunk->size - (int)chunk->data;
    if (max != 0) {
      if (chunk->data < (ulong)(long)max) {
        max = (int)chunk->data;
      }
      memcpy(pbVar4->area + pbVar4->data,chunk->area,(long)max);
      pbVar4->data = (long)max + pbVar4->data;
    }
    free_trash_chunk(chunk);
    if (pcVar5 <= start) break;
    if (pmatch[0].rm_eo == 0) {
      if (pbVar4->data < pbVar4->size) {
        cVar1 = *start;
        sVar2 = pbVar4->data;
        pbVar4->data = sVar2 + 1;
        pbVar4->area[sVar2] = cVar1;
      }
      pmatch[0].rm_eo = 1;
    }
    start = start + pmatch[0].rm_eo;
    flag = 1;
  }
  (smp->data).u.str.size = pbVar4->size;
  (smp->data).u.str.area = pbVar4->area;
  (smp->data).u.str.data = pbVar4->data;
  (smp->data).u.str.head = pbVar4->head;
  return 1;
}