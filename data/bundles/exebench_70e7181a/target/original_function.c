static inline void split(int sx1, int sy1, int sx2, int sy2,
                         int *uy1, int *uy2, int *ly1, int *ly2,
                         int num_pixels) {

 int w = sx2 - sx1 + 1;
 int cut_h;

 if (w <= 0) return;

 cut_h = num_pixels/w;

 *uy1 = sy1;
 *uy2 = sy1 + cut_h - 1;
 *ly1 = sy1 + cut_h;
 *ly2 = sy2;
}