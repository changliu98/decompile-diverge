static __inline__ void
MotionToFrameCoord(int const by,
                   int const bx,
                   int const my,
                   int const mx,
                   int * const yP,
                   int * const xP) {






    *yP = by * 8 + my;
    *xP = bx * 8 + mx;
}