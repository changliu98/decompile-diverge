void calculateSubImage(int sx1, int sy1, int sx2, int sy2, int *sy1t, int *sy2t, int *sy1b, int *sy2b, int num_pixels)
{
 int width = sx2 - sx1 + 1;
 if(width <= 0) return;

 int cut_height = num_pixels / width;
 *sy1t = sy1;
 *sy2t = sy1 + cut_height - 1;
 *sy1b = sy1 + cut_height;
 *sy2b = sy2;
}