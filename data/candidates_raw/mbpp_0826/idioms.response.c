char *getTriangleType(int a, int b, int c){
    int aSq = pow(a, 2);
    int bSq = pow(b, 2);
    int cSq = pow(c, 2);
    if(aSq == bSq + cSq || bSq == aSq + cSq || cSq == aSq + bSq){
        return "Right-angled Triangle";
    }
    if(aSq < bSq + cSq && bSq < cSq + aSq && cSq < bSq + aSq){
        return "Acute-angled Triangle";
    }
    return "Obtuse-angled Triangle";
}