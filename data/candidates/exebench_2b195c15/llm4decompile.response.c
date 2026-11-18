void swap(struct stu *stu1,struct stu *stu2)
{
 struct stu temp;
 temp = *stu1;
 *stu1 = *stu2;
 *stu2 = temp;
}