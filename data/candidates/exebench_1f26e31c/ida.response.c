void __cdecl GetLims(double *times, double t_start, double t_end, int Q, int *q_start, int *q_end)
{
  double cur_time; // [rsp+0h] [rbp-48h]
  int q; // [rsp+Ch] [rbp-3Ch]
  int end_flag; // [rsp+10h] [rbp-38h]
  int start_flag; // [rsp+14h] [rbp-34h]

  start_flag = 0;
  end_flag = 0;
  if ( Q )
  {
    for ( q = 0; q < Q; ++q )
    {
      cur_time = times[q];
      if ( start_flag == 0 && cur_time >= t_end )
      {
        *q_start = 0;
        *q_end = -1;
        start_flag = 1;
        end_flag = 1;
      }
      else if ( start_flag == 0 && cur_time >= t_start )
      {
        *q_start = q;
        start_flag = 1;
      }
      else if ( end_flag == 0 && cur_time >= t_end )
      {
        *q_end = q - 1;
        end_flag = 1;
      }
    }
    if ( start_flag )
    {
      if ( !end_flag )
        *q_end = Q - 1;
    }
    else
    {
      *q_start = 0;
      *q_end = -1;
    }
  }
  else
  {
    *q_start = 0;
    *q_end = -1;
  }
}