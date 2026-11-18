void mlCubicBezier(float Q[N][M], float D[N][M], float W[N][M], float U[N][M],
           float V[N][M], float *p) {
    *p = (1.0 / 6.0) *
         (2 * (Q[0][1] * D[0][1] + Q[0][2] * D[0][2]) +
          (Q[1][0] * D[1][0] + Q[1][2] * D[1][2]) +
          (Q[2][0] * D[2][0] + Q[2][1] * D[2][1]) + (Q[0][0] * D[0][0]) +
          (Q[1][1] * D[1][1]) + (Q[2][2] * D[2][2]));
}