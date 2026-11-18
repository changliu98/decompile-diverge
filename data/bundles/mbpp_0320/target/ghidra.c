int func0(int n)

{
  int num;
  int squareofsum;
  int sumofsquares;
  int n_local;
  
  sumofsquares = 0;
  squareofsum = 0;
  for (num = 1; num <= n; num = num + 1) {
    sumofsquares = num * num + sumofsquares;
    squareofsum = num + squareofsum;
  }
  return squareofsum * squareofsum - sumofsquares;
}