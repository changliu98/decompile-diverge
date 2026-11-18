void MatrixM(int *pos, int *dir)
{
  int x = (pos[1]*dir[3]+pos[0]*dir[1]) % 100;
  int y = (pos[3]*dir[2]+pos[2]*dir[0]) % 100;
  int z = (pos[3]*dir[3]+pos[2]*dir[1]) % 100;
  int w = (pos[1]*dir[2]+pos[0]*dir[0]) % 100;
  pos[0]=x;
  pos[1]=y;
  pos[2]=z;
  pos[3]=w;
}