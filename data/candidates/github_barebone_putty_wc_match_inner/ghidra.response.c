int wc_match_inner(char *wildcard,char *target,size_t target_len)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  char *target_end_00;
  char *save_t;
  char *save_w;
  int ret;
  char *target_end;
  size_t target_len_local;
  char *target_local;
  char *wildcard_local;
  int local_c;
  
  target_end_00 = target + target_len;
  target_local = target;
  wildcard_local = wildcard;
  if ((*wildcard == '*') ||
     (local_c = wc_match_fragment(&wildcard_local,&target_local,target_end_00), 0 < local_c)) {
    do {
      if (*wildcard_local == '\0') {
        return (uint)(target_local == target_end_00);
      }
      if (*wildcard_local != '*') {
                    /* WARNING: Subroutine does not return */
        __assert_fail("*wildcard == \'*\'","func.c",0xe4,
                      "int wc_match_inner(const char *, const char *, size_t)");
      }
      for (; *wildcard_local == '*'; wildcard_local = wildcard_local + 1) {
      }
      if (*wildcard_local == '\0') {
        return 1;
      }
      ret = 0;
      for (; pcVar2 = wildcard_local, pcVar1 = target_local, *target_local != '\0';
          target_local = target_local + 1) {
        ret = wc_match_fragment(&wildcard_local,&target_local,target_end_00);
        if (ret < 0) {
          return ret;
        }
        if (((0 < ret) && (*wildcard_local == '\0')) && (target_local != target_end_00)) {
          target_local = target_end_00 + -((long)target_local - (long)pcVar1);
          wildcard_local = pcVar2;
          iVar3 = wc_match_fragment(&wildcard_local,&target_local,target_end_00);
          return iVar3;
        }
        if (0 < ret) break;
      }
    } while (0 < ret);
    local_c = 0;
  }
  return local_c;
}