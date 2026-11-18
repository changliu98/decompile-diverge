int scaleHeight(double oldw, double neww, double oldh)
{
 return (int) ((oldh * (neww / oldw)) + .5);
}