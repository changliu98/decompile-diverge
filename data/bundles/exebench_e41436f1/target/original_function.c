void htond (double *x)
{

        int *Double_Overlay;
        int Holding_Buffer;

        Double_Overlay = (int *) x;
        Holding_Buffer = Double_Overlay [0];

        Double_Overlay [0] = htonl (Double_Overlay [1]);
        Double_Overlay [1] = htonl (Holding_Buffer);



}