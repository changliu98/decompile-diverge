void get_time_range(double *times, double t_start, double t_end, int Q, int *q_start, int *q_end)
{
  int start_flag = 0;
  int end_flag = 0;
  int q;
  double cur_time;
  if ( Q == 0 )
  {
    *q_start = 0;
    *q_end = -1;
  }
  else
  {
    for ( q = 0; q < Q; q++ )
    {
      cur_time = times[q];
      if ( ( start_flag == 0 ) && ( cur_time >= t_end ) )
      {
        *q_start = 0;
        *q_end = -1;
        start_flag = 1;
        end_flag = 1;
      }
      else if ( ( start_flag == 0 ) && ( cur_time >= t_start ) )
      {
        *q_start = q;
        start_flag = 1;
      }
      else if ( ( end_flag == 0 ) && ( cur_time >= t_end ) )
      {
        *q_end = q - 1;
        end_flag = 1;
      }
    }
    if ( start_flag == 0 )
    {
      *q_start = 0;
      *q_end = -1;
    }
    else if ( end_flag == 0 )
    {
      *q_end = Q - 1;
    }
  }
}