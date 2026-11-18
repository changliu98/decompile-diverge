void translate(struct _mat4 *mat, float x, float y)
{
  mat->data[0] = 1.0;
  mat->data[1] = 0.0;
  mat->data[2] = 0.0;
  mat->data[3] = 1.0;
  mat->data[4] = x;
  mat->data[5] = y;
}