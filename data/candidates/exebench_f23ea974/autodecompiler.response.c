void array_are_reference_type(Edge * edge)
{
 int tmp = edge->from;
 edge->from = edge->to;
 edge->to = tmp;
}