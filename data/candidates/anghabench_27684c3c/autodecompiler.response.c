int resize_height(double oldw, double neww, double oldh)
{
 return (int) ((oldh * (neww / oldw)) + .5);
}