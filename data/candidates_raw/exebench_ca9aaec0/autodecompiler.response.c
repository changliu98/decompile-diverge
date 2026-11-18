void glmMultQuaterniond(double q1[4], double q2[4], double result[4])
{
  result[1] = ((q1[2])*(q2[3])) + ((q1[3])*(q2[2])) + ((q1[0]) * (q2[0]));
  result[2] = ((q1[1])*(q2[3])) + ((q1[3])*(q2[1])) + ((q1[0]) * (q2[0]));
  result[3] = ((q1[1])*(q2[2])) + ((q1[2])*(q2[1])) + ((q1[0]) * (q2[0]));
}