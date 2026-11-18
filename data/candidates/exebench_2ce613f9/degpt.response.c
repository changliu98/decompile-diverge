void add_ang_mom(double *angular_momentum, float *center, float *position)
{
  // Update L[0] (x-component of angular momentum)
  // L_x += (y_pos - y_center) * (v_z - v_center_z) - (z_pos - z_center) * (v_y - v_center_y)
  *angular_momentum += (double)((position[1] - center[1]) * (position[5] - center[5])) - (double)((position[2] - center[2]) * (position[4] - center[4]));

  // Update L[1] (y-component of angular momentum)
  // L_y += (z_pos - z_center) * (v_x - v_center_x) - (x_pos - x_center) * (v_z - v_center_z)
  angular_momentum[1] += (double)((position[2] - center[2]) * (position[3] - center[3])) - (double)((*position - *center) * (position[5] - center[5]));

  // Update L[2] (z-component of angular momentum)
  // L_z += (x_pos - x_center) * (v_y - v_center_y) - (y_pos - y_center) * (v_x - v_center_x)
  angular_momentum[2] += (double)((*position - *center) * (position[4] - center[4])) - (double)((position[1] - center[1]) * (position[3] - center[3]));
}