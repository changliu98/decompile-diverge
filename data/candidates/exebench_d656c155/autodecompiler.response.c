int convertToBills(int dollars, int *hundreds, int *fifties, int *twenties, int *tens)
{
 *hundreds = dollars / 100;
 *fifties = (dollars % 100) / 50;
 *twenties = ((dollars % 100) % 50) / 20;
 *tens = (((dollars % 100) % 50) % 20) / 10;

 return dollars % 10;
}