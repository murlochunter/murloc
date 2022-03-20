#include<stdio.h>
#include<stdlib.h>
#include<bangtal.h> 
#include<time.h>
#pragma comment(lib,"bangtal.lib")

SceneID scene1;
ObjectID startbutton, background, restartbutton;

int arr[4][4]; // y  x
int cor_sys[4][4][2]; //0이 x좌표  1이 y좌표
ObjectID img[4][4];

int absf(int n);
void fset();
void show_a();
void randf();
int MIH();

clock_t sta, fin;
double duration;

void exch(int a, int b, int y, int x)  //a가 y좌표 b가 x좌표  y x 는 -1 좌표
{
	int i, j, t, k;

	t = arr[a][b];
	arr[a][b] = arr[y][x];
	arr[y][x] = t;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			for (t = 0; t < 4; t++)
			{
				for (k = 0; k < 4; k++)
				{
					if (i * 4 + j + 1 == arr[t][k])
					{
						locateObject(img[i][j], scene1, cor_sys[t][k][0], cor_sys[t][k][1]);
					}
				}
			}
		}
	}

	show_a();
}

void mouse_check(int a, int b) // a가 y좌표 b가 x좌표
{
	int i, j, x, y;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (arr[i][j] == 16)
			{
				x = j;
				y = i;
				i += 4;
				j += 4;
			}
		}
	}

	if (a == y && absf(b - x) == 1)
	{
		exch(a, b, y, x);
	}
	else if (b == x && absf(a - y) == 1)
	{
		exch(a, b, y, x);
	}
	if (MIH() == 1)
	{
		showObject(restartbutton);
		hideObject(background);
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				hideObject(img[i][j]);
			}
		}
		fin = clock();
		printf("%f\n", (double)(fin - sta) / CLOCKS_PER_SEC);
	}
}

void hintf()
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (arr[i][j] == 1)
			{
				arr[i][j] = arr[0][0];
				arr[0][0] = 1;
			}
			if (arr[i][j] == 5)
			{
				arr[i][j] = arr[1][0];
				arr[1][0] = 5;
			}
			if (arr[i][j] == 9)
			{
				arr[i][j] = arr[2][0];
				arr[2][0] = 9;
			}
			if (arr[i][j] == 13)
			{
				arr[i][j] = arr[3][0];
				arr[3][0] = 13;
			}
		}
	}
}

void mousetCallback(ObjectID object, int x, int y, MouseAction)
{
	int i, j, t, k;
	if (object == startbutton)
	{
		sta = clock();
		hideObject(startbutton);
		fset();
		showObject(background);
		hideObject(img[3][3]);
		randf();
	}
	else if (object == restartbutton)
	{
		sta = clock();
		hideObject(restartbutton);
		fset();
		showObject(background);
		hideObject(img[3][3]);
		randf();
	}
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (object == img[i][j])
			{
				for (t = 0; t < 4; t++)
				{
					for (k = 0; k < 4; k++)
					{
						if (arr[t][k] == i * 4 + j + 1)
						{
							mouse_check(t, k);
							i += 5;
							j += 5;
							t += 5;
							k += 5;
						}
					}
				}
			}
		}
	}

}

int main(void)
{
	int i, j;

	scene1 = createScene("퍼즐", "orignal.png");
	startbutton = createObject("start.png");
	background = createObject("background.png");
	restartbutton = createObject("restart.png");
	setMouseCallback(mousetCallback);

	locateObject(restartbutton, scene1, 100, 50);
	locateObject(background, scene1, 0, 0);
	locateObject(startbutton, scene1, 100, 150);

	showObject(startbutton);

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			arr[i][j] = i * 4 + j + 1;
		}
	}
	startGame(scene1);
}

void fset()
{
	int i, j;
	img[0][0] = createObject("1.png");
	img[0][1] = createObject("2.png");
	img[0][2] = createObject("3.png");
	img[0][3] = createObject("4.png");
	img[1][0] = createObject("5.png");
	img[1][1] = createObject("6.png");
	img[1][2] = createObject("7.png");
	img[1][3] = createObject("8.png");
	img[2][0] = createObject("9.png");
	img[2][1] = createObject("10.png");
	img[2][2] = createObject("11.png");
	img[2][3] = createObject("12.png");
	img[3][0] = createObject("13.png");
	img[3][1] = createObject("14.png");
	img[3][2] = createObject("15.png");
	img[3][3] = createObject("16.png");

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			cor_sys[i][j][0] = 300 + j * 150;
			cor_sys[i][j][1] = 470 - i * 150;
			locateObject(img[i][j], scene1, cor_sys[i][j][0], cor_sys[i][j][1]);
			showObject(img[i][j]);
		}
	}
}

int absf(int n)
{
	if (n >= 0)
		return n;
	return n * -1;
}

void show_a()
{
	hideObject(background);
	showObject(background);
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			showObject(img[i][j]);
		}
	}
	hideObject(img[3][3]);
}

void randf()
{
	int i, c = 0, a = 3, b = 3;
	while (c != 500)
	{
		i = rand() % 4;
		if (i == 0)
		{
			if (a == 0)
				continue;
			exch(a, b, a - 1, b);   //  x y  x' y' 임
			a--;
			c++;
		}
		else if (i == 1)
		{
			if (b == 3)
				continue;
			exch(a, b, a, b + 1);
			b++;
			c++;
		}
		else if (i == 2)
		{
			if (a == 3)
				continue;
			exch(a, b, a + 1, b);
			a++;
			c++;
		}
		else
		{
			if (b == 0)
				continue;
			exch(a, b, a, b - 1);
			b--;
			c++;
		}
	}
}

int MIH()
{
	int i, j, c = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (arr[i][j] == i * 4 + j + 1)
				c++;
		}
	}
	if (c == 16)
		return 1;
	return 0;
}

