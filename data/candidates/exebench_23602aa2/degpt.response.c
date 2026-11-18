void lib3ds_quat_scalar(float *result, float scalar)
{
  for (int i = 0; i < 4; i++) {
    result[i] *= scalar;
  }
}