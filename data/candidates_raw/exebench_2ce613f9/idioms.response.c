void update_line(double *line, float *pos, float *center)
{
  line[0] += (pos[1]-center[1])*(pos[5]-center[5]);
  line[0] -= (pos[2]-center[2])*(pos[4]-center[4]);
  line[1] += (pos[2]-center[2])*(pos[3]-center[3]);
  line[1] -= (pos[0]-center[0])*(pos[5]-center[5]);
  line[2] += (pos[0]-center[0])*(pos[4]-center[4]);
  line[2] -= (pos[1]-center[1])*(pos[3]-center[3]);
}