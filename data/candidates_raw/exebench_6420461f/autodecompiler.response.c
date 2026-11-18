void c_getrlimit_(long long int *softlimit, long long int *hardlimit, int *error)
{
   struct rlimit limit;
   int err;

   limit.rlim_cur = RLIM_INFINITY;
   limit.rlim_max = RLIM_INFINITY;

   if ((err = setrlimit(3, &limit)) == -1) {
      if (getrlimit(3, &limit) == 0) {
         limit.rlim_cur = limit.rlim_max;
         err = setrlimit(3, &limit);
      }
   }

   if (err != -1) {
      *error = err;
      *softlimit = -1;
      *hardlimit = -1;
      if (getrlimit(3, &limit) == 0) {
         *softlimit = limit.rlim_cur;
         *hardlimit = limit.rlim_max;
      }
   }
}