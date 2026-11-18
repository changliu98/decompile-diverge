void ComputeAndOrientation(float heading, float euler[3], float nav[3])
{
  float pitch; float roll;
  nav[0] = heading;
  pitch = euler[0];
  roll = euler[1];
  if (pitch < 0.0f)
    pitch += 360.0f;
  if (roll < 0.0f)
    roll += 360.0f;
  if (roll > 90.0f && roll < 270.0f) {
    pitch -= 180.0f;
    if (pitch < 0.0f)
      pitch += 360.0f;
  }
  if (pitch <= 180.0f)
    nav[1] = -pitch;
  else
    nav[1] = 360.0f - pitch;
  if (roll >= 0.0f && roll <= 90.0f)
    nav[2] = roll;
  else if (roll > 90.0f && roll < 270.0f)
    nav[2] = 180.0f - roll;
  else
    nav[2] = roll - 360.0f;
}