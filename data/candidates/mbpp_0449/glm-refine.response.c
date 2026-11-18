const char *__cdecl func0(int x1, int y1, int x2, int y2, int x3, int y3)
{
  // Calculate the signed area (or twice the area) of the triangle formed by the 3 points.
  // Formula derived from the determinant of the matrix:
  // | x1 y1 1 |
  // | x2 y2 1 |
  // | x3 y3 1 |
  // 
  // If the result is 0, the points are collinear (they lie on a single straight line).
  long long area = (long long)(y1 - y2) * x3 + (long long)(y3 - y1) * x2 + (long long)(y2 - y3) * x1;
  
  if (area != 0)
    return "NO";  // unk_2007
  else
    return "YES"; // unk_2004
}