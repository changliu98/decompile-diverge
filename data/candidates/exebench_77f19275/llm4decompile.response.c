void extract(char *instring,int inlength,int fieldno,int valueno,int subvalueno,int *outstart,int *outlength)
{
  int i,j,k,l,m,n,found;

  *outstart=0;
  *outlength=0;

  if (fieldno<1) {
    if (fieldno<0) return;
    if ((valueno==0) && (subvalueno==0)) {
      *outlength=inlength;
      return;
    }
    fieldno=1;
  }

  i=0;
  for (j=1;j<fieldno;j++) {
    found=0;
    while (!found) {
      if (i>=inlength) return;
      if ((instring[i]==(char)243) && (instring[i+1]==(char)190)) found=1;
      i++;
    }
    i++;
  }

  k=i;
  found=0;
  while (!found) {
    if (i>=inlength) return;
    if ((instring[i]==(char)243) && (instring[i+1]==(char)190)) found=1;
    i++;
  }
  l=i-1;

  if (valueno<1) {
    if (valueno<0) return;
    if (subvalueno==0) {
      *outstart=k;
      *outlength=l-k+1;
      return;
    }
    valueno=1;
  }

  i=k;
  for (j=1;j<valueno;j++) {
    found=0;
    while (!found) {
      if (i>=inlength) return;
      if ((instring[i]==(char)243) && (instring[i+1]==(char)191)) found=1;
      i++;
    }
    i++;
    if (i>l) return;
  }

  m=i;
  found=0;
  while (!found) {
    if (i>=l) return;
    if ((instring[i]==(char)243) && (instring[i+1]==(char)191)) found=1;
    i++;
  }
  n=i-1;

  if (subvalueno<1) {
    if (subvalueno<0) return;
    *outstart=m;
    *outlength=n-m+1;
    return;
  }

  i=m;
  for (j=1;j<subvalueno;j++) {
    found=0;
    while (!found) {
      if (i>=l) return;
      if ((instring[i]==(char)243) && (instring[i+1]==(char)192)) found=1;
      i++;
    }
    i++;
    if (i>n) return;
  }

  o=i;
  found=0;
  while (!found) {
    if (i>=n) return;
    if ((instring[i]==(char)243) && (instring[i+1]==(char)192)) found=1;
    i++;
  }
  p=i-1;

  if (p<n) {
    *outstart=o;
    *outlength=p-o+1;
  } else {
    *outstart=m;
    *outlength=n-m+1;
  }

}