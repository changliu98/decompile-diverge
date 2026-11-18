
void poly_mul1(double u1[17], double u2[17], int p1, int p2, double u3[17], int *p3)
 {






  int i, i1, i2, i3;

  double u1i;


  *p3 = p1 + p2;

  for(i=0;i<17;i++)
    u3[i] = 0.;


  for(i1=0;i1<=p1;i1++)
   {

    u1i = u1[i1];

    for(i2=0;i2<=p2;i2++)
     {

        i3 = i1 + i2;

        u3[i3] = u3[i3] + u1i*u2[i2];

     }

   }

  return;

 }
