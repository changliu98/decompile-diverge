int __cdecl conta_vota(int *voto) 
{
    // Increment the value pointed to by 'voto' and return the new value.
    // Semantically equivalent to: *voto += 1; return *voto;
    return ++*voto;
}