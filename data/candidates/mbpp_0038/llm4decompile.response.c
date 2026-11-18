double func0(int *list1, int size)
{
    int i;
    int first_even=-1,first_odd=-1;
    double res;

    for(i=0;i<size;i++){
        if(list1[i]%2==0){
            first_even=list1[i];
            break;
        }
    }

    for(i=0;i<size;i++){
        if(list1[i]%2!=0){
            first_odd=list1[i];
            break;
        }
    }

    if(first_even!=-1 && first_odd!=-1){
        res=(double)first_even/(double)first_odd;
    }
    else{
        res=-1;
    }

    return res;
}