void combain_sorted_array(int *p,int *q,int *s)

{
  int *q_end;
  int *p_end;
  int *s_local;
  int *q_local;
  int *p_local;
  
  s_local = s;
  q_local = q;
  p_local = p;
  do {
    if (p + 5 <= p_local || q + 5 <= q_local) {
      return;
    }
    if (*q_local < *p_local) {
      if (q_local == q + 4) {
        *s_local = *q_local;
        for (; s_local = s_local + 1, p_local < p + 5; p_local = p_local + 1) {
          *s_local = *p_local;
        }
      }
      *s_local = *q_local;
      q_local = q_local + 1;
    }
    else {
      if (p_local == p + 4) {
        *s_local = *p_local;
        for (; s_local = s_local + 1, q_local < q + 5; q_local = q_local + 1) {
          *s_local = *q_local;
        }
        return;
      }
      *s_local = *p_local;
      p_local = p_local + 1;
    }
    s_local = s_local + 1;
  } while( true );
}