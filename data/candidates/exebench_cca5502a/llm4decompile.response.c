int modpars_to_struct(float *valptr,int *varptr,int *maxvar,float *mpptr,float *linkvals)






{
  int success;

  success=1;
  if(*varptr==1) {
    *valptr=*mpptr;
  } else if(*varptr>*maxvar) {
    *valptr=*mpptr;
    *maxvar=*varptr;
    linkvals[*varptr-2]=*mpptr;
  } else if(*varptr>1) {
    *valptr=linkvals[*varptr-2];
    success=0;
  } else {
    success=0;
  }
  return success;
}