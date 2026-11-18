static int
MPI_Group_incl(int count, int first, int *pcount, int *parg)
{

	if (first > 0)
		*parg = 0;
	else
		*parg = count;
	return (0);
}