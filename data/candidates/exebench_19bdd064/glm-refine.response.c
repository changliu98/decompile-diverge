void __cdecl ComputeAndOrientation(float heading, float *euler, float *result)
{
  float roll;
  float pitch;

  // Assign heading to the X component of the result
  result[0] = heading;

  // Extract pitch and roll from the input euler array
  pitch = euler[0];
  roll  = euler[1];

  // Normalize pitch and roll to the [0.0, 360.0) range
  if (pitch < 0.0f)
    pitch += 360.0f;
  if (roll < 0.0f)
    roll += 360.0f;

  // If the object is upside down (roll between 90 and 270 degrees),
  // shift the pitch by 180 degrees and normalize it back to [0, 360).
  if (roll > 90.0f && roll < 270.0f)
  {
    pitch -= 180.0f;
    if (pitch < 0.0f)
      pitch += 360.0f;
  }

  // Calculate the final pitch (Y component of result)
  if (pitch > 180.0f)
    result[1] = 360.0f - pitch;
  else
    result[1] = -pitch; // Replaces the IDA Pro bitwise XOR sign flip

  // Calculate the final roll (Z component of result)
  if (roll < 0.0f || roll > 90.0f)
  {
    if (roll <= 90.0f || roll >= 270.0f)
      result[2] = roll - 360.0f;
    else
      result[2] = 180.0f - roll;
  }
  else
  {
    result[2] = roll;
  }
}