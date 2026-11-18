void GetLims(double *times, int Q, double t_start, double t_end, int *q_start, int *q_end)
{
  int q;
  int start_flag, end_flag;

  start_flag = 0;
  end_flag = 0;

  if(Q == 0) {
    *q_start = 0;
    *q_end = -1;
  }
  else {
    for(q=0; q<Q; q++) {
      if(times[q] >= t_end && !start_flag) {
 *q_start = 0;
 *q_end = -1;
 start_flag = 1;
 end_flag = 1;
      }
      else if(times[q] >= t_start && !start_flag) {
 *q_start = q;
 start_flag = 1;
      }
      else if(times[q] >= t_end && !end_flag) {
 *q_end = q-1;
 end_flag = 1;
      }
    }

    if(!start_flag)
      *q_start = 0;
    if(!end_flag)
      *q_end = Q-1;
  }
}