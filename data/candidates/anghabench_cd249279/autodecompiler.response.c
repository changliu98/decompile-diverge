int pid_to_processor_id(int pid) {
 int i = 0;
 int cpu;

 while (1) {
  if (i < ncpus) {
   if (cpu_tasks[i].pid == pid) {
    cpu = i;
    break;
   }
  } else {
   cpu = -1;
   break;
  }
  i++;
 }

 return cpu;
}