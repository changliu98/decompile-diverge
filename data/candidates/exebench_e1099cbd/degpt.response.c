void cquat_sub(double *result, double *left, double *right)
{
  // Subtract scalar component of quaternion b from a and store in q
  *result = *left - *right;
  // Subtract x component of quaternion b from a and store in q
  result[1] = left[1] - right[1];
  // Subtract y component of quaternion b from a and store in q
  result[2] = left[2] - right[2];
  // Subtract z component of quaternion b from a and store in q
  result[3] = left[3] - right[3];
}