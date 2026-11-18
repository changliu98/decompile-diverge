long long int catalan(int n){
 long long int x;
 int y= n/2;
 x = bin_coff(2*y,y);
 return x/(y+1);

}