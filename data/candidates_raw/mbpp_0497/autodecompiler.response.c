double CircularSegment(double r, double s){
 double chord = sqrt(s*s + r*r);
 double area = 3.14159265358979323846 * r * (r + chord);
 return area;
}