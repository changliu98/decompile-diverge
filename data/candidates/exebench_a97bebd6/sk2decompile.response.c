void calcula_target(int *pos, int *target, int *target_final) {
  target_final[0] = target[0] + target[0] - pos[0];
  target_final[1] = target[1] + target[1] - pos[1];
}