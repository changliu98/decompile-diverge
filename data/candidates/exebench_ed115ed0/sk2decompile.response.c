void operacao_dist(int *dist, int *dist_aux, int x, int y) {
  int x_aux, y_aux;
  x_aux = dist[0];
  y_aux = dist[1];
  dist_aux[0] = x_aux + x;
  dist_aux[1] = y_aux + y;
}