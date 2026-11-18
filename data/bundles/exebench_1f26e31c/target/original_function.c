void GetLims(double *times,double t_start,double t_end,int Q,int *q_start,int *q_end)
{
  int start_flag,end_flag;
  int q;
  double cur_time;

  start_flag = 0;
  end_flag = 0;

  if(Q==0)
    {
      *q_start = 0;
      *q_end = -1;
    }
  else
    {

      for(q=0;q<Q;q++)
 {
   cur_time = times[q];



   if((cur_time>=t_end) & (start_flag==0))
     {
       *q_start = 0;
       *q_end = -1;
       start_flag = 1;
       end_flag = 1;
     }




   else if((cur_time>=t_start) & (start_flag==0))
     {
       *q_start = q;
       start_flag = 1;
     }



   else if((cur_time>=t_end) & (end_flag==0))
     {
       *q_end = q-1;
       end_flag = 1;
     }


 }




      if(start_flag==0)
 {
   *q_start = 0;
   *q_end = -1;
 }



      else if(end_flag==0)
 *q_end = Q-1;
    }
}