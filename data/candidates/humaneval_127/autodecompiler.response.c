char* func0(int start1,int end1,int start2,int end2)
{

 int i;
 int l;
 int inter1,inter2;
 char *check;
 if(start1>start2)
 {
  inter1=start1;
 }
 else
 {
  inter1=start2;
 }
 if(end1<end2)
 {
  inter2=end1;
 }
 else
 {
  inter2=end2;
 }
 l=inter2-inter1;
 if(l<3)
 {
  check="NO";
 }
 else
 {
  for(i=2;i*i<=l;i++)
  {
   if(l%i==0)
   {
    check="NO";
    break;
   }
   else
   {
    check="YES";
   }
  }
 }
 return(check);
}