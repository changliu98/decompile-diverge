#include <netinet/in.h>

void htonf (float *x)
{

        int *Float_Overlay;
        int Holding_Buffer;

        Float_Overlay = (int *) x;
        Holding_Buffer = Float_Overlay [0];

        Float_Overlay [0] = htonl (Holding_Buffer);



}
