void reverse(char s[])
{
    char *head, *tail, t;

    for (tail = s; *tail; ++tail)
        ;

    for (head = s; head < --tail; ++head)
        t = *head, *head = *tail, *tail = t;
}