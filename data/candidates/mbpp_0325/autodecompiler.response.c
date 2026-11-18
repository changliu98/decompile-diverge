int func0(int p1){
    int t1;
    int t2;
    int t3;
    int t4;
    int t5;
    int t6;
    if(p1 <= 3){
        t1 = p1;
    } else {
        t2 = p1;
        t3 = 1;
        while(t3 <= p1){
            t4 = t3 * t3;
            if(t4 > p1){
                break;
            }
            t5 = t2;
            t6 = func0(p1 - t4) + 1;
            if(t5 < t6){
                t1 = t2;
            } else {
                t1 = func0(p1 - t4) + 1;
            }
            t2 = t1;
            t3 = t3 + 1;
        }
    }
    return t1;
}