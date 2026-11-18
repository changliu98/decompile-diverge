int

getboundingbox(int nV, double *Vertex, double *bb)




{
   int i,j,k1,k2,k3,k;
   double min[3],max[3];

   for(j=0; j<3; j++)
   {
      min[j] = Vertex[j];
      max[j] = Vertex[j];
   }

   for(i=1; i<nV; i++)
   {
      for(j=0; j<3; j++)
      {
         if(Vertex[i*3+j] < min[j])
            min[j] = Vertex[i*3+j];
         if(Vertex[i*3+j] > max[j])
            max[j] = Vertex[i*3+j];
      }
   }

   for(j=0; j<3; j++)
   {
      bb[j] = (min[j] + max[j])/2.0;
   }

   for(j=0; j<3; j++)
   {
      bb[j+3] = 1.0;
      while((bb[j+3] * (max[j] - min[j])) < 1.0)
         bb[j+3] *= 2.0;
      while((bb[j+3] * (max[j] - min[j])) > 1.0)
         bb[j+3] /= 2.0;
   }


   k1 = 3;
   k2 = 4;
   k3 = 5;

   if(bb[k1] > bb[k2])
   {
      k = k1;
      k1 = k2;
      k2 = k;
   }
   if(bb[k2] > bb[k3])
   {
      k = k2;
      k2 = k3;
      k3 = k;
   }
   if(bb[k1] > bb[k2])
   {
      k = k1;
      k1 = k2;
      k2 = k;
   }

   if(bb[k1] < bb[k2]/1.0)
      bb[k1] = bb[k2]/1.0;
   if(bb[k3] > bb[k2]*1.0)
      bb[k3] = bb[k2]*1.0;

   return(0);
}