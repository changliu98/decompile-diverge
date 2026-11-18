int setLoopIters(double dt, double tmax, double max_time,
                 unsigned int *loop_iters) {
  double t;
  t = dt * tmax * (double)(*loop_iters);
  if (t > max_time) {
    *loop_iters = (unsigned int)((double)(*loop_iters) * max_time / t);
    if (*loop_iters < 2) *loop_iters = 2;
  }
  return 0;
}