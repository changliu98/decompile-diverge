int func0(int mask[3])
{
 int i, j;
 int uniq[3];
 int u;

 uniq[0] = mask[0];
 uniq[1] = mask[1];
 uniq[2] = mask[2];

 u = 0;
 memset(uniq, 0, sizeof(uniq));
 for(i = 0; i < 4; i++) {
  bool found = false;
  for(j = 0; j < i; j++) {
   if(uniq[j] == uniq[i]) {
    found = true;
    break;
   }
  }
  if(!found) u++;
 }

 int ret;
 if(u == 3) ret = 0;
 else ret = 4 - u;

 return ret;
}