void euler_to_quaternion(float *quaternion)
{
  float temp;
  float temp1;
  float temp2;
  temp = quaternion[0];
  temp1 = quaternion[1] * 0.0174524f;
  temp1 += quaternion[2] * 0.9998477f;
  temp1 = -temp1;
  temp2 = quaternion[1] * 0.0174524f;
  temp2 += quaternion[2] * 0.9998477f;
  temp2 = temp2 * 0.06975647f;
  quaternion[0] = quaternion[0] * 0.99756408f;
  quaternion[0] += temp2;
  quaternion[1] = quaternion[1] * 0.99756408f;
  quaternion[1] += temp;
  quaternion[2] = quaternion[2] * 0.99756408f;
  quaternion[2] += temp1;
}