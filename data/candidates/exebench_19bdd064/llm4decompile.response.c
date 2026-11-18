void ComputeAndOrientation(float heading, float *euler, float *result)
{
  float pitch, roll;

  result[0] = heading;
  pitch = euler[0];
  roll = euler[1];

  if (pitch < 0)
    pitch += 2.0 * 3.14159265358979323846;
  if (roll < 0)
    roll += 2.0 * 3.14159265358979323846;

  if (roll > 3.14159265358979323846 / 2.0 && roll < 3.0 * 3.14159265358979323846 / 2.0)
  {
    pitch -= 3.14159265358979323846;
    if (pitch < 0)
      pitch += 2.0 * 3.14159265358979323846;
  }

  if (pitch <= 3.14159265358979323846 / 2.0)
    result[1] = -pitch;
  if (pitch > 3.14159265358979323846 / 2.0)
    result[1] = 2.0 * 3.14159265358979323846 - pitch;

  if (roll >= 0 && roll <= 3.14159265358979323846 / 2.0)
    result[2] = roll;
  else if (roll > 3.14159265358979323846 / 2.0 && roll < 3.0 * 3.14159265358979323846 / 2.0)
    result[2] = 3.14159265358979323846 - roll;
  else
    result[2] = roll - 2.0 * 3.14159265358979323846;
}