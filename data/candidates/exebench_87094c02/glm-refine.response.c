Scales a 3D vector u by a scalar c
void __cdecl r3scal(double u[3], double c)
{
    for (int i = 0; i < 3; ++i) {
        u[i] *= c;
    }
}