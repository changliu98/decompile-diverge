int NumStalls(int* schedule, int* intervals, int len) {
 int i = 0;
 int j = 0;
 int numIntervals = 0;

 while (1) {

  while ((i < len) && (schedule[i] == 0)) {
   i++;
  }

  if (i >= len) {
   break;
  }


  while ((i < len) && (schedule[i] != 0)) {
   i++;
  }

  int interval = 0;


  while ((i < len) && (schedule[i] == 0)) {
   i++;
   interval++;
  }

  if (i >= len) {
   break;
  }
  intervals[numIntervals] = interval;
  numIntervals++;
 }

 return numIntervals + 1;
}