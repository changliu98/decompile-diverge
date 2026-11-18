char ** func0(char *text,int *count)

{
  long lVar1;
  int iVar2;
  size_t sVar3;
  char *pcVar4;
  char *__src;
  undefined8 uStack_c0;
  char acStack_b8 [8];
  char *local_b0;
  char *word;
  int end;
  int start;
  char *p;
  unsigned_long __vla_expr0;
  char *local_88;
  int word_count;
  char pattern [16];
  regmatch_t matches [1];
  regex_t regex;
  int *count_local;
  char *text_local;
  
                    /* Unresolved local var: char[143] str@[???] */
  pattern._0_8_ = s__b_a_zA_Z__5__b_00102010._0_8_;
  pattern._8_8_ = s__b_a_zA_Z__5__b_00102010._8_8_;
  word_count = 0;
  uStack_c0 = 0x10125e;
  sVar3 = strlen(text);
  __vla_expr0 = sVar3 + 1;
  lVar1 = -(sVar3 + 0x10 & 0xfffffffffffffff0);
  local_b0 = acStack_b8 + lVar1;
  local_88 = acStack_b8;
  *(undefined8 *)((long)&uStack_c0 + lVar1) = 0x101297;
  strcpy(acStack_b8 + lVar1,text);
  *(undefined8 *)((long)&uStack_c0 + lVar1) = 0x1012a9;
  regcomp((regex_t *)&regex,pattern,1);
  p = local_b0;
  while( true ) {
    pcVar4 = p;
    *(undefined8 *)((long)&uStack_c0 + lVar1) = 0x1012d3;
    iVar2 = regexec((regex_t *)&regex,pcVar4,1,(regmatch_t *)matches,0);
    if (iVar2 != 0) break;
    start = matches[0].rm_so;
    end = matches[0].rm_eo;
    iVar2 = matches[0].rm_eo - matches[0].rm_so;
    *(undefined8 *)((long)&uStack_c0 + lVar1) = 0x101309;
    pcVar4 = malloc((long)(iVar2 + 1));
    __src = p + start;
    iVar2 = end - start;
    word = pcVar4;
    *(undefined8 *)((long)&uStack_c0 + lVar1) = 0x10133c;
    strncpy(pcVar4,__src,(long)iVar2);
    word[end - start] = '\0';
    func0::words[word_count] = word;
    p = p + end;
    word_count = word_count + 1;
  }
  *(undefined8 *)((long)&uStack_c0 + lVar1) = 0x10139e;
  regfree((regex_t *)&regex);
  *count = word_count;
  return func0::words;
}