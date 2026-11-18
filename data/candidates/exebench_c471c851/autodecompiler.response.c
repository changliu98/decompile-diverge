void stb_linear_controller(float *current, float target, float p_gain, float d_gain, float dt)
{
 float error, diff;
 float sign = 1.0f;
 float tmp;

 error = *current;
 if (error == target) return;

 if (error > target) {
  target = -target;
  error = -error;
  sign = -1.0f;
 }

 if (error < 0) {
  tmp = error + dt * d_gain;
  if (tmp > 0) {
   tmp = 0;
   dt -= error / d_gain;
   if (dt < 0) dt = 0;
  }
  error = tmp;
 }

 tmp = error + dt * p_gain;
 if (tmp > target) tmp = target;
 *current = tmp * sign;
}