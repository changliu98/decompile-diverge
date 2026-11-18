void agrega(int *head, int *tail, int i, int *ll){
 if(*head==-1){
  *head=i;
  *tail=i;
 }else{
  ll[*tail]=i;
  *tail=i;
 }
 ll[*tail]=-1;
 return;
}