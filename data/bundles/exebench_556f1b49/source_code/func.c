





int MPI_Group_incl(int group, int n, int *ranks, int *newgroup)
{
   if (n > 0)
     *newgroup = 0;
   else
     *newgroup = group;
   return 0;
}
