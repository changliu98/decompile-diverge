void image_fit(int original_width, int original_height, int max_width, int max_height, unsigned int *new_width, unsigned int *new_height, char keep_ratio) {

 float width_ratio = ((float)original_height/(float)original_width);
 float height_ratio = ((float)max_height/(float)max_width);

 if(keep_ratio<1 || keep_ratio>2)
  keep_ratio = (width_ratio < height_ratio) ? 1 : 2;

 switch(keep_ratio) {
  case 1 :
   *new_height = (unsigned int)((float)max_width * width_ratio);
   *new_width = max_width;
   break;
  case 2 :
   *new_width = (unsigned int)((float)max_height / width_ratio);
   *new_height = max_height;
   break;
 }
}