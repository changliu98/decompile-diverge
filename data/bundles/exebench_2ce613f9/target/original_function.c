void add_ang_mom(double L[3], float c[6], float pos[6]) {


  L[0] += (pos[1]-c[1])*(pos[2 +3]-c[2 +3]);
  L[0] -= (pos[2]-c[2])*(pos[1 +3]-c[1 +3]);
  L[1] += (pos[2]-c[2])*(pos[0 +3]-c[0 +3]);
  L[1] -= (pos[0]-c[0])*(pos[2 +3]-c[2 +3]);
  L[2] += (pos[0]-c[0])*(pos[1 +3]-c[1 +3]);
  L[2] -= (pos[1]-c[1])*(pos[0 +3]-c[0 +3]);

}