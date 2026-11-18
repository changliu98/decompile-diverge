void GetLims(double *times,double t_start,double t_end,int Q,int *q_start,int *q_end)

{
  double dVar1;
  bool bVar2;
  bool bVar3;
  double cur_time;
  int q;
  int end_flag;
  int start_flag;
  int *q_end_local;
  int *q_start_local;
  int Q_local;
  double t_end_local;
  double t_start_local;
  double *times_local;
  
  bVar2 = false;
  bVar3 = false;
  if (Q == 0) {
    *q_start = 0;
    *q_end = -1;
  }
  else {
    for (q = 0; q < Q; q = q + 1) {
      dVar1 = times[q];
      if (dVar1 < t_end || bVar2) {
        if (dVar1 < t_start || bVar2) {
          if (t_end <= dVar1 && !bVar3) {
            *q_end = q + -1;
            bVar3 = true;
          }
        }
        else {
          *q_start = q;
          bVar2 = true;
        }
      }
      else {
        *q_start = 0;
        *q_end = -1;
        bVar2 = true;
        bVar3 = true;
      }
    }
    if (bVar2) {
      if (!bVar3) {
        *q_end = Q + -1;
      }
    }
    else {
      *q_start = 0;
      *q_end = -1;
    }
  }
  return;
}