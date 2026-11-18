void add_ang_mom(double L[3], float c[6], float pos[6]) {







    L[0] += (pos[1]-c[1])*(pos[5]-c[5]) - (pos[2]-c[2])*(pos[4]-c[4]);
    L[1] += (pos[2]-c[2])*(pos[3]-c[3]) - (pos[0]-c[0])*(pos[5]-c[5]);
    L[2] += (pos[0]-c[0])*(pos[4]-c[4]) - (pos[1]-c[1])*(pos[3]-c[3]);
}