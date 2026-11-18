void r3cpsc(r3vector *result, const r3vector *v, double c)
{
  result->x = v->x * c;
  result->y = v->y * c;
  result->z = v->z * c;
}