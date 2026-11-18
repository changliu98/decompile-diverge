void rotate_point(float *point) {
  float x = point[0];
  float y = point[1];
  float z = point[2];
  float y_rad = y * 0.0174524;
  float z_rad = z * 0.0174524;
  float x_rot = x * 0.99756408;
  float y_rot = y * 0.99984771;
  float z_rot = z * 0.99756408;
  float z_rot_2 = z * 0.069756471;
  point[0] = x_rot - z_rot_2;
  point[1] = y_rot - y_rad;
  point[2] = z_rot + z_rad;
}