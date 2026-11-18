void swi_coortrf2(double v[3], double vr[3], double s, double c){
    double temp[3];
    temp[0] = v[0];
    temp[1] = v[1]*c + v[2]*s;
    temp[2] = -v[1]*(s) + v[2]*c;

    vr[0] = temp[0];
    vr[1] = temp[1];
    vr[2] = temp[2];
}