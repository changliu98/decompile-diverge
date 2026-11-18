void swap(struct student *a, struct student *b)
{
 int temp;
 temp = a->no;
 a->no = b->no;
 b->no = temp;

 temp = a->age;
 a->age = b->age;
 b->age = temp;

 temp = a->score;
 a->score = b->score;
 b->score = temp;
}