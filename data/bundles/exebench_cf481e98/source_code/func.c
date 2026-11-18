
void Sqrt(float x,float* res){
    float xhalf = 0.5f * x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i >> 1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);
    if(x>0){

        *res =1/x;
    }else{
        *res=0;
    }
    return;
}
