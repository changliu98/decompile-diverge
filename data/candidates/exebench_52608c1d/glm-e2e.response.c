void MatrixM(struct Matrix *m1, struct Matrix *m2) {
    int a = (m1->a * m2->a + m1->b * m2->c) % 100;
    int b = (m1->a * m2->b + m1->b * m2->d) % 100;
    int c = (m1->c * m2->a + m1->d * m2->c) % 100;
    int d = (m1->c * m2->b + m1->d * m2->d) % 100;

    m1->a = a;
    m1->b = b;
    m1->c = c;
    m1->d = d;
}