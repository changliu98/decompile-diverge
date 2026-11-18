int func0(int x1,int x2,int x3)
{
   int m;

   if (x1>x2) {
      if (x1<x3) m = x1;
      else if (x2>x3) m = x2;
      else m = x3;
   } else {
      if (x1>x3) m = x1;
      else if (x2<x3) m = x2;
      else m = x3;
   }

   return(m);
}