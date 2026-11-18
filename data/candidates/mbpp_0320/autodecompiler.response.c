int func0(int n) {
  int i, sumofsquares = 0, squareofsum = 0;
  for(i = 1; ; i++) {
    if(i <= n) {
      sumofsquares += i * i;
      squareofsum += i;
    } else {
      break;
    }
  }
  squareofsum *= squareofsum;
  return squareofsum - sumofsquares;
}