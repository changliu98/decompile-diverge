void cylinder(float r, float h, float *csa, float *tsa, float *vol){
 *csa = 2*r*h*22/7;
 *tsa = 2*r*(h+r)*22/7;
 *vol = r*r*h*22/7;
}