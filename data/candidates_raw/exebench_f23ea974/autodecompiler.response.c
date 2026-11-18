void Swap(Edge * edge)
{
 int tmp = edge->from;
 edge->from = edge->to;
 edge->to = tmp;
}