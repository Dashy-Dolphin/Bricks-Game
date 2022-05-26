#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
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
int score = 0, lives = 5;
int py = 471, px = 251, pl = 30;
int bx = 252, by = 462, bdx = -6, bdy = -6;

int win = 0;
const int row = 19, col = 4;
int blocks[row][col];

int min(int a, int b)
{
    return (a < b) ? a : b;
}
int max(int a, int b)
{
    return (a > b) ? a : b;
}

void color4(int x, int a, int b, int c, int d)
{
    int poly[8] = {a, b, a, d, c, d, c, b};

    setcolor(BLACK);
    if (x == 0)
    {

        setfillstyle(1, BLACK);
        fillpoly(4, poly);
    }
    else
    {

        setfillstyle(1, WHITE);
        fillpoly(4, poly);
    }
}
void print(int a, int b, int x)
{
    char title[100] = {0};
    int g = x;

    int i = 0;

    while (g > 0)
    {
        title[i] = char('0' + g % 10);
        i++;
        g /= 10;
    }

    int left = 0, right = i - 1;

    while (left < right)
    {
        char x = title[left];
        title[left] = title[right];
        title[right] = x;
        left++;
        right--;
    }

    color4(0, a, b, a + 60, b + 60);
    setcolor(WHITE);
    outtextxy(a, b, title);
}

void printinit()
{
    char x1[20] = "SCORE : ";
    char x2[20] = "LIVES : ";
    x1[8] = 0;
    x2[8] = 0;
    settextstyle(0, HORIZ_DIR, 4);

    outtextxy(10, 10, x1);

    outtextxy(318, 10, x2);

    outtextxy(200, 10, "0");

    print(518, 10, lives);
}

void initializer()
{

    cleardevice();

    setlinestyle(0, 1, 1);
    line(0, 0, 636, 0);
    line(0, 93, 636, 93);

    line(0, 477, 0, 0);
    line(636, 0, 636, 477);
    line(0, 477, 636, 477);
    printinit();
    int startx = 6;
    int starty = 162;

    int relx = 0;
    int rely = 0;

    int i, j;

    for (i = 0; i < col; i++)
    {
        for (j = 0; j < row; j++)
        {
            blocks[j][i] = 1;

            color4(1, startx + relx, starty + rely, startx + relx + 30, starty + rely + 12);

            relx += 33;
        }

        relx = 0;
        rely += 15;
    }

    color4(1, px, py, px + pl, py + 1);

    fillellipse(bx, by, 3, 3);
}

int collidechecker(int i, int j)
{
    int a = bx;
    int b = by;

    int t1 = 6 + i * 33;
    int t2 = 162 + j * 15;

    int t3 = 36 + i * 33;
    int t4 = 174 + j * 15;
    int key = 0;

    int h = 3;
    if (abs(a + 3 - t1) <= h)
    {
        if (t2 <= b && b <= t4)
        {
            bdx *= -1;
            key = 1;
        }
    }

    if (abs(a - 3 - t3) <= h)
    {
        if (t2 <= b && b <= t4)
        {
            bdx *= -1;
            key = 1;
        }
    }

    if (abs(b + 3 - t2) <= h)
    {
        if (t1 <= a && a <= t3)
        {
            bdy *= -1;
            key = 1;
        }
    }

    if (abs(b - 3 - t4) <= h)
    {
        if (t1 <= a && a <= t3)
        {
            bdy *= -1;
            key = 1;
        }
    }

    if (key > 0)
    {
        bx += bdx;
        by += bdy;
    }

    return key;
}

void padmover()
{

    // f for left 5  and j for right 5 ;
    char c = 'a'; // default return

    int mseconds = 40;
    while (mseconds != 0)
    {
        if (kbhit())
        { // if there is a key in keyboard buffer
            c = getch();
            fflush(stdin); // get the char
            break;         // we got char! No need to wait anymore...
        }

        delay(1);   // one second sleep
        --mseconds; // countdown a second
    }

    // f and j for short jump; //d and j for long jump

    if (c == 'f')
    {
        color4(0, px, py, px + pl, py + 1);
        px = max(px - 15, 0);
        color4(1, px, py, px + pl, py + 1);
    }
    else if (c == 'j')
    {
        color4(0, px, py, px + pl, py + 1);
        px = min(px + 15, 636 - pl);
        color4(1, px, py, px + pl, py + 1);
    }
    else if (c == 'd')
    {
        color4(0, px, py, px + pl, py + 1);
        px = max(px - 45, 0);
        color4(1, px, py, px + pl, py + 1);
    }
    else if (c == 'k')
    {
        color4(0, px, py, px + pl, py + 1);
        px = min(px + 45, 636 - pl);
        color4(1, px, py, px + pl, py + 1);
    }
}
int ballmover()
{
    int a = bx + bdx;
    int b = by + bdy;

    setfillstyle(1, BLACK);
    setcolor(BLACK);
    fillellipse(bx, by, 3, 3);
    color4(1, px, py, px + pl, py + 1);

    int ans = 0, cou = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (blocks[i][j] == 1)
            {
                cou += 1;
                if (collidechecker(i, j) == 1)
                {
                    ans += 1;
                    blocks[i][j] = 0;
                    int t1 = 6 + i * 33;
                    int t2 = 162 + j * 15;

                    int t3 = 36 + i * 33;
                    int t4 = 174 + j * 15;

                    color4(0, t1, t2, t3, t4);
                }
            }
        }
    }

    if (cou == 0)
    {
        win = 1;
        return 0;
    }

    if (ans > 0)
    {
        score += ans;
        a = bx;
        b = by;

        color4(0, 200, 10, 317, 99);

        print(200, 10, score);
    }
    else
    {

        if (b <= 96)
        {

            bdy *= -1;
        }

        if (b >= 468)
        {
            line(0, 477, 636, 477);

	    if (px - 9 <= a && a <= px + pl + 9)
            {
                if (a <= px + pl / 3 || a >= px + (2 * pl) / 3)
                {
                    if (abs(bdy) == 6)
                    {
                        bdy /= 2;
                        bdy *= -1;
                    }
                }
                else
                {

                    if (bdy < 0)
                        bdy = 6;
                    else
                        bdy = -6;
                }


               
            }
            else
            {
                return 0;
            }
        }

        if (a >= 633)
        {

            bdx *= -1;
            if (a + bdx >= 633)
            {
                setfillstyle(1, WHITE);
                setcolor(WHITE);

                fillellipse(a, b, 3, 3);
                bx = a + 2 * bdx;
                by = b + 2 * bdy;

                line(0, 0, 636, 0);
                line(0, 93, 636, 93);

                line(0, 477, 0, 0);
                line(636, 0, 636, 477);
                line(0, 477, 636, 477);

                return 1;
            }
        }

        if (a <= 3)
        {

            bdx *= -1;

            if (a + bdx <= 3)
            {
                setfillstyle(1, WHITE);
                setcolor(WHITE);

                fillellipse(a, b, 3, 3);
                bx = a + 2 * bdx;
                by = b + 2 * bdy;

                line(0, 0, 636, 0);
                line(0, 93, 636, 93);

                line(0, 477, 0, 0);
                line(636, 0, 636, 477);
                line(0, 477, 636, 477);

                return 1;
            }
        }
    }

    setfillstyle(1, WHITE);
    setcolor(WHITE);

    fillellipse(a, b, 3, 3);
    bx = a;
    by = b;

    line(0, 0, 636, 0);
    line(0, 93, 636, 93);

    line(0, 477, 0, 0);
    line(636, 0, 636, 477);
    line(0, 477, 636, 477);
    return 1;
}

void runner()
{
    initializer();
    getch();

    while (lives--)
    {

        bx = 252;
        by = 462;
        bdx = -6;
        bdy = -6;
        while (ballmover() == 1)
        {

            padmover();

            delay(50);
        }

        if (win == 1)
        {
            cleardevice();
            outtextxy(200, 300, "YOU WIN!");
            break;
        }

        color4(0, 518, 10, 630, 99);
        print(518, 10, lives);
    }

    if (win == 0)
    {
        cleardevice();
        outtextxy(200, 300, "YOU LOSE!");
    }
}
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



int main(void)
{

    int gdriver = DETECT, gmode = 1, errorcode;

    /* initialize graphics mode */
    initgraph(&gdriver, &gmode, "");

    /* read result of initialization */
    errorcode = graphresult();

    if (errorcode != grOk) /* an error occurred */
    {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        printf("Press any key to halt:");
        getch();
        exit(1); /* return with error code */
    }

    Render_title();
    getch();
    runner();
    getch();

    closegraph();
    return 0;
}