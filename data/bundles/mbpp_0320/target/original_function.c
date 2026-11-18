int func0(int n) {
  int sumofsquares = 0;
  int squareofsum = 0;
  for (int num = 1; num <= n; num++) {
    sumofsquares += num * num;
    squareofsum += num;
  }
  squareofsum = squareofsum * squareofsum;
  return squareofsum - sumofsquares;
}