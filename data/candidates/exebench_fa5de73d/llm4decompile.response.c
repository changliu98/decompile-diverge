void
QuaternionMult( QUAT *pQOut, QUAT *pQIn1, QUAT *pQIn2 )
{






 pQOut->w = -pQIn1->x * pQIn2->x - pQIn1->y * pQIn2->y - pQIn1->z * pQIn2->z - pQIn1->w * pQIn2->w;
 pQOut->x = pQIn1->x * pQIn2->w + pQIn1->y * pQIn2->z - pQIn1->z * pQIn2->y + pQIn1->w * pQIn2->x;
 pQOut->y = -pQIn1->x * pQIn2->z + pQIn1->y * pQIn2->w + pQIn1->z * pQIn2->x + pQIn1->w * pQIn2->y;
 pQOut->z = pQIn1->x * pQIn2->y - pQIn1->y * pQIn2->x + pQIn1->z * pQIn2->w + pQIn1->w * pQIn2->z;

}