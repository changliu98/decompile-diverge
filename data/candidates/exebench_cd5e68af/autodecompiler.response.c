void merge(int *left, int *right, int *mainlist)
{
int i=0,j=0,k=0;
for(;;)
 {
 char _tmp0_1;
 if(_tmp0_1 = (i<7))
  _tmp0_1 = (j<7);
 if(!_tmp0_1)
  break;
 if(left[i] < right[j])
  mainlist[k++] = left[i++];
 else
  mainlist[k++] = right[j++];
 }

while(i<7)
 mainlist[k++] = left[i++];

while(j<7)
 mainlist[k++] = right[j++];

}