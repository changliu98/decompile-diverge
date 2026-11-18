int rectInsideCircle(int r){
 int x,y;
 int rectangles = 0;
 int diameter = r*2;
 int diameterSquare = diameter*diameter;

 for(x=1;x<2*r;x++){
  for(y=1;y<2*r;y++){
   int diagnalLengthSquare = (x)*(x) + (y)*(y);
   if(diagnalLengthSquare <= diameterSquare){
    rectangles++;
   }
  }
 }

 return rectangles;
}