void Mat4_T(float mat[16])
{
    float t;
    {(t) = (mat[1]); (mat[1]) = (mat[4]); (mat[4]) = (t);};
    {(t) = (mat[2]); (mat[2]) = (mat[8]); (mat[8]) = (t);};
    {(t) = (mat[3]); (mat[3]) = (mat[12]); (mat[12]) = (t);};

    {(t) = (mat[6]); (mat[6]) = (mat[9]); (mat[9]) = (t);};
    {(t) = (mat[7]); (mat[7]) = (mat[13]); (mat[13]) = (t);};
    {(t) = (mat[11]); (mat[11]) = (mat[14]); (mat[14]) = (t);};
}