#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include <math.h>

double determinant_3x3(float inp[9])
{
    int i, j;
    double det = 0.0;
    double m[3][3] = {
        {0.0 }
    };

    for ( i = 0; i < 3; i++ )
        for ( j = 0; j < 3; j++ )
            m[i][j] = inp[i + 3 * j];

    det = m[0][0]*(m[1][1] * m[2][2] - m[1][2] * m[2][1]);
    det += -m[0][1]*(m[1][0] * m[2][2] - m[1][2] * m[2][0]);
    det += m[0][2]*(m[1][0] * m[2][1] - m[1][1] * m[2][0]);

    return det;
}
