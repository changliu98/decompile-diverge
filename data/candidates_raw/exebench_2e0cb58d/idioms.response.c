void vadd(struct vector *res, struct vector *in1, struct vector *in2){
  res->x = in1->x + in2->x;
  res->y = in1->y + in2->y;
  res->z = in1->z + in2->z;
}