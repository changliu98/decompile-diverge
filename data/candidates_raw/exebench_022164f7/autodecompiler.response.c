int tri_tri_intersect_with_isectline(double V0[3],double V1[3],double V2[3],
 double U0[3],double U1[3],double U2[3],int *coplanar,
 double isectpt1[3],double isectpt2[3]) {
 double E1[3],E2[3];
 double N1[3],N2[3],d1,d2;
 double du0,du1,du2,dv0,dv1,dv2;
 double D[3];
 double isect1[2], isect2[2];
 double isectpointA1[3],isectpointA2[3];
 double isectpointB1[3],isectpointB2[3];
 double isectpointZ1[3],isectpointZ2[3];
 double du0du1,du0du2,dv0dv1,dv0dv2;
 short index;
 double vp0,vp1,vp2;
 double up0,up1,up2;
 double b,c,max,min;

 E1[0]=V1[0]-V0[0]; E1[1]=V1[1]-V0[1]; E1[2]=V1[2]-V0[2];;
 E2[0]=V2[0]-V0[0]; E2[1]=V2[1]-V0[1]; E2[2]=V2[2]-V0[2];;
 D[0]=-(dir[1]*E2[2]-dir[2]*E2[1]); D[1]=-(dir[2]*E2[0]-dir[0]*E2[2]); D[2]=-(dir[0]*E2[1]-dir[1]*E2[0]);;

 d1 = -(D[0]*(V0[0]-U0[0]) + D[1]*(V0[1]-U0[1]) + D[2]*(V0[2]-U0[2]));
 if (fabs(d1)<0.00001) {
  du0=(V0[0]-U0[0]); du1=(V1[0]-U0[0]); du2=(V2[0]-U0[0]);
  dv0=(V0[1]-U0[1]); dv1=(V1[1]-U0[1]); dv2=(V2[1]-U0[1]);
  if ((du0<0 && du1<0 && du2<0) || (du0>0 && du1>0 && du2>0)) return 0;
  du0du1=du0*du1;
  du0du2=du0*du2;
  if (du0du1>0.0f && du0du2>0.0f)
   return 0;
  dv0dv1=dv0*dv1;
  dv0dv2=dv0*dv2;
  if (dv0dv1>0.0f && dv0dv2>0.0f)
   return 0;
  else {
   max = du0; min = du1; if (du1>max) { min = du1; if (du2>max) max = du2; }
   if (du2<min) min = du2;
   vp0 = du0; vp1 = du1; vp2 = du2;
   du0du1 = du0du1; du0du2 = du0du2; dv0dv1 = dv0dv1; dv0dv2 = dv0dv2;
  }
  du0du1 = du0du1; du0du2 = du0du2; dv0dv1 = dv0dv1; dv0dv2 = dv0dv2;
  if (du0du1>0.0f && du0du2>0.0f) {
   isect1[0] = du0; isect1[1] = du1;
   isect2[0] = du0; isect2[1] = du2;
   isectpointA1[0] = V0[0]; isectpointA1[1] = V1[0]; isectpointA1[2] = V2[0];;
   isectpointA2[0] = V0[0]; isectpointA2[1] = V1[0]; isectpointA2[2] = V2[0];;
   isectpointZ1[0] = dv0; isectpointZ1[1] = dv1; isectpointZ1[2] = dv2;;
   isectpointZ2[0] = dv0; isectpointZ2[1] = dv1; isectpointZ2[2] = dv2;;
  } else if (du0du1<0.0f && du0du2<0.0f) {
   isect1[0] = du0; isect1[1] = du2;
   isect2[0] = du0; isect2[1] = du1;
   isectpointA1[0] = V0[0]; isectpointA1[1] = V2[0]; isectpointA1[2] = V1[0];;
   isectpointA2[0] = V0[0]; isectpointA2[1] = V2[0]; isectpointA2[2] = V1[0];;
   isectpointZ1[0] = dv0; isectpointZ1[1] = dv2; isectpointZ1[2] = dv1;;
   isectpointZ2[0] = dv0; isectpointZ2[1] = dv2; isectpointZ2[2] = dv1;;
  } else if (du1du2>0.0f && du0du1>0.0f) {
   isect1[0] = du1; isect1[1] = du2;
   isect2[0] = du0; isect2[1] = du1;
   isectpointA1[0] = V1[0]; isectpointA1[1] = V2[0]; isectpointA1[2] = V0[0];;
   isectpointA2[0] = V0[0]; isectpointA2[1] = V1[0]; isectpointA2[2] = V1[0];;
   isectpointZ1[0] = dv1; isectpointZ1[1] = dv2; isectpointZ1[2] = dv0;;
   isectpointZ2[0] = dv0; isectpointZ2[1] = dv1; isectpointZ2[2] = dv1;;
  } else if (du1du2<0.0f && du0du1<0.0f) {
   isect1[0] = du1; isect1[1] = du0;
   isect2[0] = du1; isect2[1] = du2;
   isectpointA1[0] = V1[0]; isectpointA1[1] = V0[0]; isectpointA1[2] = V1[0];;
   isectpointA2[0] = V1[0]; isectpointA2[1] = V2[0]; isectpointA2[2] = V1[0];;
   isectpointZ1[0] = dv1; isectpointZ1[1] = dv0; isectpointZ1[2] = dv1;;
   isectpointZ2[0] = dv1; isectpointZ2[1] = dv2; isectpointZ2[2] = dv1;;
  } else if (du2du0>0.0f && du0du1>0.0f) {
   isect1[0] = du2; isect1[1] = du0;
   isect2[0] = du1; isect2[1] = du2;
   isectpointA1[0] = V2[0]; isectpointA1[1] = V0[0]; isectpointA1[2] = V1[0];;
   isectpointA2[0] = V2[0]; isectpointA2[1] = V2[0]; isectpointA2[2] = V1[0];;
   isectpointZ1[0] = dv2; isectpointZ1[1] = dv0; isectpointZ1[2] = dv1;;
   isectpointZ2[0] = dv1; isectpointZ2[1] = dv2; isectpointZ2[2] = dv2;;
  } else if (du2du0<0.0f && du0du1<0.0f) {
   isect1[0] = du2; isect1[1] = du1;
   isect2[0] = du2; isect2[1]