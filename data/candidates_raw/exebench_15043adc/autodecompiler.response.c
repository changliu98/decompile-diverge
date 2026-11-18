void InitCPUTime(CPUTIME *totaltime, CPUTIME *childtime,
                 CPUTIME *parenttime)
{
   *totaltime = 0;
   *childtime = 0;
   *parenttime = 1;
}