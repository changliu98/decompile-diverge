int func0(int prevGuess, int newGuess)
{
 int correctGuess;

 if(newGuess < prevGuess)
  correctGuess = -1;
 else if(newGuess == prevGuess && newGuess % 2 == 1)
  correctGuess = -1;
 else if(newGuess % 2 == 1)
  correctGuess = newGuess - 1;
 else
  correctGuess = newGuess;

 return correctGuess;
}