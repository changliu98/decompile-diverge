float func0(float arr[], int n)
{
    int low, high ;
    int median;
    float key;

    low = 0 ; high = n-1 ; median = (low + high) / 2;
    for (;;) {

        if (high <= low)
            return arr[median] ;

        if (high == low + 1) {
            if (arr[low] > arr[high])
                { float temp = (arr[low]);(arr[low]) = (arr[high]);(arr[high]) = temp; } ;
            return arr[median] ;
        }


    low = (low + high) / 2;


    if (arr[low] > arr[high]) { float temp = (arr[low]);(arr[low]) = (arr[high]);(arr[high]) = temp; } ;


    if (arr[low-1] > arr[high]) {
        { float temp = (arr[low-1]);(arr[low-1]) = (arr[high]);(arr[high]) = temp; } ;
        if (arr[low] > arr[high]) { float temp = (arr[low]);(arr[low]) = (arr[high]);(arr[high]) = temp; } ;
    }


    if (arr[low+1] > arr[high]) {
        { float temp = (arr[low+1]);(arr[low+1]) = (arr[high]);(arr[high]) = temp; } ;
        if (arr[low] > arr[high]) { float temp = (arr[low]);(arr[low]) = (arr[high]);(arr[high]) = temp; } ;
    }


    if (arr[low] > arr[low+1]) { float temp = (arr[low]);(arr[low]) = (arr[low+1]);(arr[low+1]) = temp; } ;


    key = arr[low];


    for (;;) {
        low++;
        while (arr[low] < key) low++;


        high--;
        while (key < arr[high]) high--;


        if (high < low)
        break;


        { float temp = (arr[low]);(arr[low]) = (arr[high]);(arr[high]) = temp; } ;
    }


    if (high < median)
        low = high + 1;
    if (high >= median)
        high = low - 1;
    }
}