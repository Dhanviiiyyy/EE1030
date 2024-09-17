float findK_a(int x1, int y1, int x2, int y2, int x3)
{
float k = ((float)(y2*(x1-x3)+y1*(x3-x2)))/(x1-x2);
return k;
}
float findK_b(int x1, int y1, int y2, int x3, int y3)
{
float k =(x1*(y2-y3)+x3*(y1-y2))/(y1-y3);
return k;
}



