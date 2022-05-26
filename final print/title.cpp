int title1[7][17];
int title2[7][27];

int B[7][3] = {{1, 1, 0}, {1, 0, 1}, {1, 0, 1}, {1, 1, 0}, {1, 0, 1}, {1, 0, 1}, {1, 1, 0}};
int R[7][3] = {{1, 1, 0}, {1, 0, 1}, {1, 0, 1}, {1, 1, 0}, {1, 1, 0}, {1, 0, 1}, {1, 0, 1}};
int I[7][3] = {{1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}};
int C[7][3] = {{0, 1, 1}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {0, 1, 1}};
int K[7][3] = {{1, 0, 1}, {1, 0, 1}, {1, 1, 0}, {1, 1, 0}, {1, 0, 1}, {1, 0, 1}, {1, 0, 1}};
int Space[7][3] = {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}, {2, 2, 2}, {2, 2, 2}, {2, 2, 2}, {2, 2, 2}};
int E[7][3] = {{1, 1, 1}, {1, 0, 0}, {1, 0, 0}, {1, 1, 0}, {1, 0, 0}, {1, 0, 0}, {1, 1, 1}};
int A[7][3] = {{0, 1, 0}, {1, 0, 1}, {1, 0, 1}, {1, 0, 1}, {1, 1, 1}, {1, 0, 1}, {1, 0, 1}};

void alphabet_encode(int *a, int col, int y, int *cha)
{
    for (int i = 0; i < 7; i++)
    {
	for (int j = 0; j < 3; j++)
	{
	    *((a + i * col) + y + j) = *((cha + i * 3) + j);
	}
    }
}
void scolor4(int x, int a, int b, int c, int d)
{
    int poly[8] = {a, b, a, d, c, d, c, b};

    if (x == 0)
    {
	 setcolor(BLACK);
	setfillstyle(1, BLACK);
	fillpoly(4, poly);
    }
    else
    {
	 setcolor(WHITE);
	setfillstyle(1, WHITE);
	fillpoly(4, poly);
    }
}
void title_encode()
{
    // Brick
    alphabet_encode((int *)title1, 17, 0, (int *)B);
    alphabet_encode((int *)title1, 17, 3, (int *)Space);
    alphabet_encode((int *)title1, 17, 4, (int *)R);
    alphabet_encode((int *)title1, 17, 7, (int *)Space);
    alphabet_encode((int *)title1, 17, 8, (int *)I);
    alphabet_encode((int *)title1, 17, 9, (int *)Space);
    alphabet_encode((int *)title1, 17, 10, (int *)C);
    alphabet_encode((int *)title1, 17, 13, (int *)Space);
    alphabet_encode((int *)title1, 17, 14, (int *)K);

    // Breaker
    alphabet_encode((int *)title2, 27, 0, (int *)B);
    alphabet_encode((int *)title2, 27, 3, (int *)Space);
    alphabet_encode((int *)title2, 27, 4, (int *)R);
    alphabet_encode((int *)title2, 27, 7, (int *)Space);
    alphabet_encode((int *)title2, 27, 8, (int *)E);
    alphabet_encode((int *)title2, 27, 11, (int *)Space);
    alphabet_encode((int *)title2, 27, 12, (int *)A);
    alphabet_encode((int *)title2, 27, 15, (int *)Space);
    alphabet_encode((int *)title2, 27, 16, (int *)K);
    alphabet_encode((int *)title2, 27, 19, (int *)Space);
    alphabet_encode((int *)title2, 27, 20, (int *)E);
    alphabet_encode((int *)title2, 27, 23, (int *)Space);
    alphabet_encode((int *)title2, 27, 24, (int *)R);
}

void print_title(int *title, int col, int startx, int starty, int width)
{
    int relx = 0, rely = 0;
    int i, j;
    setlinestyle(0,1,1);
    for (i = 0; i < 7; i++)
    {
	for (j = 0; j < col; j++)
	{
	    int x = *((title + i * col) + j);

	    if (x == 1)
	    {
		scolor4(1, startx + relx, starty + rely, startx + relx + 2 * width - 1, starty + rely + width - 1);
		relx += 2 * width;
	    }
	    else if (x == 0)
	    {
		scolor4(0, startx + relx, starty + rely, startx + relx + 2 * width , starty + rely + width);
		relx += 2 * width;
	    }
	    else
	    {
		scolor4(0, startx + relx, starty + rely, startx + relx + 3 * width , starty + rely + width);
		relx += 3 * width;
	    }





	}

	relx = 0;
	rely += width;
    }
}

void Render_title()
{
    cleardevice();
    title_encode();

    int a, b;

    for (int i = 1; i < 10; i += 2)
    {

	a = 18 * i - i/2;
	b = 3 * i + i / 2;
	print_title((int *)title1, 17, 319 - a, 235 - 2*b, i);

	a = 28 * i + i / 2;

	print_title((int *)title2, 27, 319 - a, 240 , i);

	delay(500);
    }


}
