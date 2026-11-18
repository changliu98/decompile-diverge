void get_icm_field(char *buf, int l, int fieldno, int valueno, int subvalueno,
                   int *rpos, int *rlen)
{
int pos, fstart, fend, vstart, vend, sstart, send;
int i;

*rpos=0; *rlen=0;

if (fieldno<=0) {
  if ((fieldno<0) || (valueno!=0) || (subvalueno!=0)) return;
  *rlen=l;
  return;
}

pos=0;
for(i=1;i<fieldno;i++) {
  while((pos<l) && (((*(buf+pos))!='\033') || (*(buf+pos+1))!='\076'))
    pos++;
  if (pos>=l) return;
  pos+=2;
}
fstart=pos;
while((pos<l) && (((*(buf+pos))!='\033') || (*(buf+pos+1))!='\076')) pos++;
fend=pos;
if (valueno<=0) {
  if ((valueno<0) || (subvalueno!=0)) return;
  *rpos=fstart;
  *rlen=fend-fstart;
  return;
}

pos=fstart;
for(i=1;i<valueno;i++) {
  while((pos<l) && (((*(buf+pos))!='\033') || (*(buf+pos+1))!='\075'))
    pos++;
  if (pos>=l) return;
  pos+=2;
  if (pos>fend) return;
}
vstart=pos;
while((pos<fend) && (((*(buf+pos))!='\033') || (*(buf+pos+1))!='\075')) pos++;
vend=pos;
if (subvalueno<=0) {
  if (subvalueno<0) return;
  *rpos=vstart;
  *rlen=vend-vstart;
} else {

  pos=vstart;
  for(i=1;i<subvalueno;i++) {
    while((pos<l) && (((*(buf+pos))!='\033') || (*(buf+pos+1))!='\074'))
      pos++;
    if (pos>=l) return;
    pos++;
    if (pos>vend) return;
  }
  sstart=pos;
  while((pos<vend) && (((*(buf+pos))!='\033') || (*(buf+pos+1))!='\074'))
    pos++;
  send=pos;
  if (send>=vend) {
    *rpos=vstart;
    *rlen=vend-vstart;
  } else {
    *rpos=sstart;
    *rlen=send-sstart;
  }
}
}