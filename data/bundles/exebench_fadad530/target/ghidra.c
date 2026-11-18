void ToIUPAC(char *seq,int is_aseq)

{
  char *pcVar1;
  int is_aseq_local;
  char *seq_local;
  
  seq_local = seq;
  if (is_aseq == 0) {
    for (; *seq_local != '\0'; seq_local = seq_local + 1) {
      pcVar1 = strchr("ACGTUNRYMKSWHBVDacgtunrymkswhbvd",(int)*seq_local);
      if (pcVar1 == (char *)0x0) {
        *seq_local = 'N';
      }
    }
  }
  else {
    for (; *seq_local != '\0'; seq_local = seq_local + 1) {
      pcVar1 = strchr("ACGTUNRYMKSWHBVDacgtunrymkswhbvd",(int)*seq_local);
      if ((((pcVar1 == (char *)0x0) && (*seq_local != ' ')) && (*seq_local != '.')) &&
         (((*seq_local != '_' && (*seq_local != '-')) && (*seq_local != '~')))) {
        *seq_local = 'N';
      }
    }
  }
  return;
}