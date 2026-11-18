void __cdecl stb_linear_controller(float *curpos, float target_pos, float acc, float deacc, float dt)
{
  float cp = *curpos;

  if (cp == target_pos)
    return;

  float sign = 1.0f;
  float target_abs = target_pos;

  // If moving in the negative direction, mirror the problem into the positive domain
  if (cp > target_pos)
  {
    // Equivalent to flipping the sign bit of the floats
    cp = -cp;
    target_abs = -target_pos;
    sign = -1.0f;
  }

  // Phase 1: Deceleration to zero velocity (if currently overshooting the origin)
  if (cp < 0.0f)
  {
    float p = cp + deacc * dt;
    if (p <= 0.0f)
    {
      // Still moving towards 0, no time left for acceleration
      dt = 0.0f;
    }
    else
    {
      // Reached 0 before the full dt elapsed, remaining time can be used for acceleration
      dt -= cp / deacc;
      if (dt < 0.0f)
        dt = 0.0f;
      cp = 0.0f;
    }
  }

  // Phase 2: Acceleration towards the target
  float pa = cp + acc * dt;
  if (pa > target_abs)
    pa = target_abs;

  // Restore original direction and apply
  *curpos = pa * sign;
}