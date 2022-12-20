#define _USE_MATH_DEFINES

#include <SDL.h>
#include <algorithm>
#include <iostream>
#include <conio.h>
#include <string>

const int frameHeight = 1000;
const int frameWidth = 1000;
const int N = 2;
const int M = 4;
const int L = 3;
const int speed = 5;
const float S = 1.1;
const float s = 0.9;
const float angle = M_PI / 180;
const float xA = 50, yA = 480, zA = 0, xB = 150, yB = 480, zB = 300, xC = 480, yC = 480, zC = 300, xV = 300, yV = 150, zV = 150;
const float xa = 200, ya = 480, za = 0, xb = 200, yb = 480, zb = 230, xc = 380, yc = 580, zc = 330, xv = 150, yv = 200, zv = 150;


void multiply(float lin[N][M], float matrix[M][M])
{
	float res[N][M] = { {0, 0, 0, 0}, {0, 0, 0, 0} };

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			for (int k = 0; k < M; k++)
			{
				res[i][j] += (lin[i][k] * matrix[k][j]);
			}
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			lin[i][j] = res[i][j];
		}
	}
}

void lines(float lin[N][M] ,float xc ,float yc , float zc, int axis, float angle) 
{
	
		float first_rot[M][M] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {-xc, -yc, -zc,1} };
		float second_rot[M][M] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {xc, yc, zc, 1}};



		float X_m_rotate[M][M] = { {cos(angle), 0, sin(angle), 0}, {0, 1, 0, 0}, {-sin(angle),0, cos(angle), 0}, {0 ,0 , 0, 1} };
		float Y_m_rotate[M][M] = { {1, 0, 0, 0}, {0, cos(angle), sin(angle), 0}, {0, -sin(angle), cos(angle), 0}, {0, 0, 0, 1} };
		float Z_m_rotate[M][M] = { {cos(angle), sin(angle), 0, 0}, {-sin(angle), cos(angle), 0,0}, {0, 0, 1, 0}, {0 ,0 , 0, 1} };
		float m_scale[M][M] = { {S,0,0,0},{0,S,0,0} ,{0,0,S,0}, {0, 0, 0, 1 } };
		multiply(lin, first_rot);
		if (axis == 1) {
			multiply(lin, X_m_rotate);
		}
		if (axis == 2) {
			multiply(lin, Y_m_rotate);
		}
		if (axis == 3) {
			multiply(lin, Z_m_rotate);
		}
		if (axis == 4) {
			multiply(lin, m_scale);
		}
		multiply(lin, second_rot);
	}

void scale (float lin[N][M], float xc, float yc, float zc,float S)
{

	float first_rot[M][M] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {-xc, -yc, -zc,1} };
	float second_rot[M][M] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {xc, yc, zc, 1} };
	float m_scale[M][M] = { {S,0,0,0},{0,S,0,0} ,{0,0,S,0}, {0, 0, 0, 1 } };
	multiply(lin, first_rot);
	multiply(lin, m_scale);
	multiply(lin, second_rot);
}


void rotateX(float line1[N][M], float line2[N][M], float line3[N][M], float line4[N][M], float line5[N][M], float line6[N][M], float Line1[N][M], float Line2[N][M], float Line3[N][M], float Line4[N][M], float Line5[N][M], float Line6[N][M], float angle)
{
	float xc = (line1[0][0] + line2[0][0] + line3[0][0] + line4[1][0] + Line1[0][0] + Line2[0][0] + Line3[0][0] + Line4[1][0]) / 8,
		yc = (line1[0][1] + line2[0][1] + line3[0][1] + line4[1][1] + Line1[0][1] + Line2[0][1] + Line3[0][1] + Line4[1][1]) / 8,
		zc = (line1[0][2] + line2[0][2] + line3[0][2] + line4[1][2] + Line1[0][2] + Line2[0][2] + Line3[0][2] + Line4[1][2]) / 8;
	float first_rot[M][M] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {-xc, -yc, -zc,
	1} };
	float second_rot[M][M] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {xc, yc, zc, 1}
	};
	float m_rotate[M][M] = { {cos(angle), 0, sin(angle), 0}, {0, 1, 0, 0}, {-sin(angle),
	0, cos(angle), 0}, {0 ,0 , 0, 1} };
	int axis = 1;
	lines(line1, xc, yc, zc, axis, angle);
	lines(line2, xc, yc, zc, axis, angle);
	lines(line3, xc, yc, zc, axis, angle);
	lines(line4, xc, yc, zc, axis, angle);
	lines(line5, xc, yc, zc, axis, angle);
	lines(line6, xc, yc, zc, axis, angle);
	lines(Line1, xc, yc, zc, axis, angle);
	lines(Line2, xc, yc, zc, axis, angle);
	lines(Line3, xc, yc, zc, axis, angle);
	lines(Line4, xc, yc, zc, axis, angle);
	lines(Line5, xc, yc, zc, axis, angle);
	lines(Line6, xc, yc, zc, axis, angle);
	
}

void rotateY(float line1[N][M], float line2[N][M], float line3[N][M], float line4[N][M], float line5[N][M], float line6[N][M], float Line1[N][M], float Line2[N][M], float Line3[N][M], float Line4[N][M], float Line5[N][M], float Line6[N][M], float angle)
{
	float xc = (line1[0][0] + line2[0][0] + line3[0][0] + line4[1][0] + Line1[0][0] + Line2[0][0] + Line3[0][0] + Line4[1][0]) / 8,
		yc = (line1[0][1] + line2[0][1] + line3[0][1] + line4[1][1] + Line1[0][1] + Line2[0][1] + Line3[0][1] + Line4[1][1]) / 8,
		zc = (line1[0][2] + line2[0][2] + line3[0][2] + line4[1][2] + Line1[0][2] + Line2[0][2] + Line3[0][2] + Line4[1][2]) / 8;
	
	int axis = 2;
	lines(line1, xc, yc, zc, axis, angle);
	lines(line2, xc, yc, zc, axis, angle);
	lines(line3, xc, yc, zc, axis, angle);
	lines(line4, xc, yc, zc, axis, angle);
	lines(line5, xc, yc, zc, axis, angle);
	lines(line6, xc, yc, zc, axis, angle);
	lines(Line1, xc, yc, zc, axis, angle);
	lines(Line2, xc, yc, zc, axis, angle);
	lines(Line3, xc, yc, zc, axis, angle);
	lines(Line4, xc, yc, zc, axis, angle);
	lines(Line5, xc, yc, zc, axis, angle);
	lines(Line6, xc, yc, zc, axis, angle);
	
}

void rotateZ(float line1[N][M], float line2[N][M], float line3[N][M], float line4[N][M], float line5[N][M], float line6[N][M], float Line1[N][M], float Line2[N][M], float Line3[N][M], float Line4[N][M], float Line5[N][M], float Line6[N][M], float angle)
{
	float xc = (line1[0][0] + line2[0][0] + line3[0][0] + line4[1][0] + Line1[0][0] + Line2[0][0] + Line3[0][0] + Line4[1][0]) / 8,
		yc = (line1[0][1] + line2[0][1] + line3[0][1] + line4[1][1] + Line1[0][1] + Line2[0][1] + Line3[0][1] + Line4[1][1]) / 8,
		zc = (line1[0][2] + line2[0][2] + line3[0][2] + line4[1][2] + Line1[0][2] + Line2[0][2] + Line3[0][2] + Line4[1][2]) / 8;
	
	int axis = 3;
	lines(line1, xc, yc, zc, axis, angle);
	lines(line2, xc, yc, zc, axis, angle);
	lines(line3, xc, yc, zc, axis, angle);
	lines(line4, xc, yc, zc, axis, angle);
	lines(line5, xc, yc, zc, axis, angle);
	lines(line6, xc, yc, zc, axis, angle);
	lines(Line1, xc, yc, zc, axis, angle);
	lines(Line2, xc, yc, zc, axis, angle);
	lines(Line3, xc, yc, zc, axis, angle);
	lines(Line4, xc, yc, zc, axis, angle);
	lines(Line5, xc, yc, zc, axis, angle);
	lines(Line6, xc, yc, zc, axis, angle);
	
}

void scaling(float line1[N][M], float line2[N][M], float line3[N][M], float line4[N][M], float line5[N][M], float line6[N][M], float Line1[N][M], float Line2[N][M], float Line3[N][M], float Line4[N][M], float Line5[N][M], float Line6[N][M], float S)
{
	float xc = (line1[0][0] + line2[0][0] + line3[0][0] + line4[1][0] + Line1[0][0] + Line2[0][0] + Line3[0][0] + Line4[1][0]) / 8,
		yc = (line1[0][1] + line2[0][1] + line3[0][1] + line4[1][1] + Line1[0][1] + Line2[0][1] + Line3[0][1] + Line4[1][1]) / 8,
		zc = (line1[0][2] + line2[0][2] + line3[0][2] + line4[1][2] + Line1[0][2] + Line2[0][2] + Line3[0][2] + Line4[1][2]) / 8;
	
	int axis = 4;
	scale(line1, xc, yc, zc, S);
	scale(line2, xc, yc, zc, S);
	scale(line3, xc, yc, zc, S);
	scale(line4, xc, yc, zc, S);
	scale(line5, xc, yc, zc, S);
	scale(line6, xc, yc, zc, S);
	scale(Line1, xc, yc, zc, S);
	scale(Line2, xc, yc, zc, S);
	scale(Line3, xc, yc, zc, S);
	scale(Line4, xc, yc, zc, S);
	scale(Line5, xc, yc, zc, S);
	scale(Line6, xc, yc, zc, S);

	}

SDL_Window* Window = NULL;
SDL_Renderer* Render = NULL;

void paintOverTriangle(float line1[N][M], float line2[N][M], float line3[N][M])
{
	float x1 = line1[0][0], y1 = line1[0][1];
	float x2 = line1[1][0], y2 = line1[1][1];
	float x3 = line2[1][0], y3 = line2[1][1];
	float xmin, xmax;
	float k12, k23, k31;

	x1 == x2 ? k12 = 0 : k12 = (y2 - y1) / (x2 - x1);
	x2 == x3 ? k23 = 0 : k23 = (y3 - y2) / (x3 - x2);
	x1 == x3 ? k31 = 0 : k31 = (y1 - y3) / (x1 - x3);

	float b12 = y1 - k12 * x1, b23 = y2 - k23 * x2, b31 = y3 - k31 * x3;
	float X, Y1, Y2;

	xmin = fmin(fmin(x1, x2), x3);
	xmax = fmax(fmax(x1, x2), x3);

	for (X = xmin; X < xmax; X++)
	{
		if (xmin == x1 && xmax == x3) {
			Y1 = X * k31 + b31;
			if (X < x2) {
				Y2 = X * k12 + b12;
			}
			else {
				Y2 = X * k23 + b23;
			}
		}
		else if (xmin == x1) {
			Y1 = X * k12 + b12;
			if (X < x3) {
				Y2 = X * k31 + b31;
			}
			else {
				Y2 = X * k23 + b23;
			}
		}
		else if (xmin == x2 && xmax == x3) {
			Y1 = X * k23 + b23;
			if (X < x1) {
				Y2 = X * k12 + b12;
			}
			else {
				Y2 = X * k31 + b31;
			}
		}
		else if (xmin == x2) {
			Y1 = X * k12 + b12;
			if (X < x3) {
				Y2 = X * k23 + b23;
			}
			else {
				Y2 = X * k31 + b31;
			}
		}
		else if (xmin == x3 && xmax == x1) {
			Y1 = X * k31 + b31;
			if (X < x2) {
				Y2 = X * k23 + b23;
			}
			else {
				Y2 = X * k12 + b12;
			}
		}
		else if (xmin == x3) {
			Y1 = X * k23 + b23;
			if (X < x1) {
				Y2 = X * k31 + b31;
			}
			else {
				Y2 = X * k12 + b12;
			}
		}
		SDL_RenderDrawLine(Render, X, Y1, X, Y2);
	}
	
}

bool compare(int x1, int x2) { return x1 > x2; }

void paintOver(float line1[N][M], float line2[N][M], float line3[N][M], float line4[N][M], float line5[N][M], float line6[N][M],
	float Line1[N][M], float Line2[N][M], float Line3[N][M], float Line4[N][M], float Line5[N][M], float Line6[N][M])
{

	int zc1 = (line1[0][2] + line2[0][2] + line3[0][2]) / 3;
	int zc2 = (line1[0][2] + line1[1][2] + line4[1][2]) / 3;
	int zc3 = (line2[0][2] + line2[1][2] + line4[1][2]) / 3;
	int zc4 = (line3[0][2] + line3[1][2] + line4[1][2]) / 3;
	int zc1_sec = (Line1[0][2] + Line2[0][2] + Line3[0][2]) / 3;
	int zc2_sec = (Line1[0][2] + Line1[1][2] + Line4[1][2]) / 3;
	int zc3_sec = (Line2[0][2] + Line2[1][2] + Line4[1][2]) / 3;
	int zc4_sec = (Line3[0][2] + Line3[1][2] + Line4[1][2]) / 3;
	int mxz[8] = { zc1, zc2, zc3, zc4, zc1_sec, zc2_sec, zc3_sec, zc4_sec };
	float line1_cut[N][M] = { {0,0,0,1}, {0,0,0,1} }, line2_cut[N][M] = { {0,0,0,1}, {0,0,0,1} };

	std::sort(mxz, mxz + 8, compare);
	
	for (int i = 1; i < 8; i++)
	{
		if (mxz[i] == zc1) {
			SDL_SetRenderDrawColor(Render, 0, 255, 255, 255);

			paintOverTriangle(line1, line2, line3);

		}
		if (mxz[i] == zc2) {
			SDL_SetRenderDrawColor(Render, 0, 206, 209, 255);

			paintOverTriangle(line1, line4, line5);
		}
		if (mxz[i] == zc3) {
			SDL_SetRenderDrawColor(Render, 64, 224, 208, 255);
			
			paintOverTriangle(line2, line5, line6);
		}
		if (mxz[i] == zc4) {
			SDL_SetRenderDrawColor(Render, 0, 139, 139, 255);
			paintOverTriangle(line3, line6, line4);
		}
		if (mxz[i] == zc1_sec) {
			SDL_SetRenderDrawColor(Render, 128, 0, 0, 255);
			
			paintOverTriangle(Line1, Line2, Line3);

		}
		if (mxz[i] == zc2_sec) {
			SDL_SetRenderDrawColor(Render, 139, 0, 0, 255);

			paintOverTriangle(Line1, Line4, Line5);
		}
		if (mxz[i] == zc3_sec) {
			SDL_SetRenderDrawColor(Render, 178, 34, 34, 255);

			paintOverTriangle(Line2, Line5, Line6);
		}
		if (mxz[i] == zc4_sec) {
			SDL_SetRenderDrawColor(Render, 220, 20, 60, 255);

			paintOverTriangle(Line3, Line6, Line4);
		}
	}
}

bool Init() 
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << SDL_GetError() << std::endl;
	else {
		Window = SDL_CreateWindow("Lines", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, frameWidth, frameHeight, SDL_WINDOW_SHOWN);
		if (Window == NULL)
			std::cout << SDL_GetError() << std::endl;
		else
			Render = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	}
	return success;
}

void up (float line1[N][M], float line2[N][M], float line3[N][M], float line4[N][M], float
	line5[N][M], float line6[N][M]) 
{
	line1[0][1] -= speed;
	line1[1][1] -= speed;
	line2[0][1] -= speed;
	line2[1][1] -= speed;
	line3[0][1] -= speed;
	line3[1][1] -= speed;
	line4[0][1] -= speed;
	line4[1][1] -= speed;
	line5[0][1] -= speed;
	line5[1][1] -= speed;
	line6[0][1] -= speed;
	line6[1][1] -= speed;
}

void down(float line1[N][M], float line2[N][M], float line3[N][M], float line4[N][M], float
	line5[N][M], float line6[N][M]) {
	line1[0][1] += speed;
	line1[1][1] += speed;
	line2[0][1] += speed;
	line2[1][1] += speed;
	line3[0][1] += speed;
	line3[1][1] += speed;
	line4[0][1] += speed;
	line4[1][1] += speed;
	line5[0][1] += speed;
	line5[1][1] += speed;
	line6[0][1] += speed;
	line6[1][1] += speed;
}

void left(float line1[N][M], float line2[N][M], float line3[N][M], float line4[N][M], float
	line5[N][M], float line6[N][M]) {
	line1[0][0] -= speed;
	line1[1][0] -= speed;
	line2[0][0] -= speed;
	line2[1][0] -= speed;
	line3[0][0] -= speed;
	line3[1][0] -= speed;
	line4[0][0] -= speed;
	line4[1][0] -= speed;
	line5[0][0] -= speed;
	line5[1][0] -= speed;
	line6[0][0] -= speed;
	line6[1][0] -= speed;
}

void right(float line1[N][M], float line2[N][M], float line3[N][M], float line4[N][M], float
	line5[N][M], float line6[N][M]) {
	line1[0][0] += speed;
	line1[1][0] += speed;
	line2[0][0] += speed;
	line2[1][0] += speed;
	line3[0][0] += speed;
	line3[1][0] += speed;
	line4[0][0] += speed;
	line4[1][0] += speed;
	line5[0][0] += speed;
	line5[1][0] += speed;
	line6[0][0] += speed;
	line6[1][0] += speed;
}

void toUser(float line1[N][M], float line2[N][M], float line3[N][M], float line4[N][M],
	float line5[N][M], float line6[N][M]) {
	line1[0][2] -= speed;
	line1[1][2] -= speed;
	line2[0][2] -= speed;
	line2[1][2] -= speed;
	line3[0][2] -= speed;
	line3[1][2] -= speed;
	line4[0][2] -= speed;
	line4[1][2] -= speed;
	line5[0][2] -= speed;
	line5[1][2] -= speed;
	line6[0][2] -= speed;
	line6[1][2] -= speed;
}

void fromUser(float line1[N][M], float line2[N][M], float line3[N][M], float line4[N][M],
	float line5[N][M], float line6[N][M]) {
	line1[0][2] += speed;
	line1[1][2] += speed;
	line2[0][2] += speed;
	line2[1][2] += speed;
	line3[0][2] += speed;
	line3[1][2] += speed;
	line4[0][2] += speed;
	line4[1][2] += speed;
	line5[0][2] += speed;
	line5[1][2] += speed;
	line6[0][2] += speed;
	line6[1][2] += speed;
}

using namespace std;

namespace geometry
{
	typedef struct point
	{
		double x;
		double y;
		double z;
	};

	typedef struct vector_
	{
		double x;
		double y;
		double z;
	};


	typedef struct line
	{
		point p;
		vector_ s;
	};

	typedef struct plane
	{
		double A;
		double B;
		double C;
		double D;
	};

	line point_point2line(point p1, point p2)
	{
		//прямая по 2 точкам
		return line{ p2, vector_{p1.x - p2.x, p1.y - p2.y, p1.z - p2.z} };
	}

	line paral_line_through_point(line l, point p)
	{
		//прямая параллельная данной через точку
		return line{ p, l.s };
	}

	point intersection_line_plane(line l, plane p)
	{

		if ((p.A * (l.s.x) + p.B * (l.s.y) + p.C * (l.s.z)) == 0)
		{
			cout << "ERR div by zero!\n\n";
			return point{ 0,0,0 };
		}
		double t = (-(p.A * (l.p.x) + p.B * (l.p.y) + p.C * (l.p.z) + p.D)) / (p.A * (l.s.x) + p.B * (l.s.y) + p.C * (l.s.z));


		return point{ l.p.x + l.s.x * t, l.p.y + l.s.y * t, l.p.z + l.s.z * t };
	
	}
}

void triangle_shadow(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
	//построение тени для треугольника

	int xPl[3];
	int yPl[3];
	int zPl[3];
	xPl[0] = 0; yPl[0] = 780; zPl[0] = -80;//-80
	xPl[1] = 300; yPl[1] = 780; zPl[1] = 20;
	xPl[2] = 150; yPl[2] = 900; zPl[2] = 180;//180

	int A = (yPl[1] - yPl[0]) * (zPl[2] - zPl[0]) - (yPl[2] - yPl[0]) * (zPl[1] - zPl[0]);
	int B = (zPl[1] - zPl[0]) * (xPl[2] - xPl[0]) - (zPl[2] - zPl[0]) * (xPl[1] - xPl[0]);
	int C = (xPl[1] - xPl[0]) * (yPl[2] - yPl[0]) - (xPl[2] - xPl[0]) * (yPl[1] - yPl[0]);
	int D = -(A * xPl[0] + B * yPl[0] + C * zPl[0]);

	geometry::plane p{ A,B,C,D };
	geometry::vector_ v{ A,B,C};//вектор нормали, перпендикуляр к плоскости. 

	geometry::point p1{x1, y1, z1};
	geometry::point p2{x2, y2, z2};
	geometry::point p3{x3, y3, z3};

	geometry::line l1{p1, v};//перпендикуляры к плоскости и точек треугольника
	geometry::line l2{p2, v};
	geometry::line l3{p3, v};

	geometry::point s1 = geometry::intersection_line_plane(l1, p);//точка пересечения этих перпендикуляров с плоскостью
	geometry::point s2 = geometry::intersection_line_plane(l2, p);
	geometry::point s3 = geometry::intersection_line_plane(l3, p);

	SDL_SetRenderDrawColor(Render, 100, 100, 100, 255);
	float Line1[N][M] = { {s1.x, s1.y, s1.z, 1}, {s2.x, s2.y, s2.z, 1} },
		Line2[N][M] = { {s1.x, s1.y, s1.z, 1}, {s3.x, s3.y, s3.z, 1} },
		Line3[N][M] = { {s3.x, s3.y, s3.z, 1}, {s2.x, s2.y, s2.z, 1} };
	paintOverTriangle(Line1, Line2, Line3);//строим тень из полученных треугольников

}

void shadow(float line1[N][M], float line2[N][M], float line3[N][M], float line4[N][M], float
	line5[N][M], float line6[N][M])
{
	//тень строится для каждой грани отдельно.
	triangle_shadow(line1[0][0], line1[0][1], line1[0][2], line1[1][0], line1[1][1], line1[1][2], line2[1][0], line2[1][1], line2[1][2]);

	triangle_shadow(line1[0][0], line1[0][1], line1[0][2], line1[1][0], line1[1][1], line1[1][2], line4[1][0], line4[1][1], line4[1][2]);
	triangle_shadow(line1[0][0], line1[0][1], line1[0][2], line2[1][0], line2[1][1], line2[1][2], line4[1][0], line4[1][1], line4[1][2]);
	triangle_shadow(line2[1][0], line2[1][1], line2[1][2], line1[1][0], line1[1][1], line1[1][2], line4[1][0], line4[1][1], line4[1][2]);

	return;
}

int main(int argc, char* argv[])
{
	float line1[N][M] = { { 0, 0, 0, 1 }, {0, 0, 0, 1} }, line2[N][M] = { {0, 0, 0, 1 }, {0, 0, 0, 1} }, line3[N][M] = { { 0, 0, 0, 1 }, {0, 0, 0, 1} };
	float line4[N][M] = { { 0, 0, 0, 1 }, {0, 0, 0, 1 } }, line5[N][M] = { { 0, 0, 0, 1 }, {0, 0, 0, 1} }, line6[N][M] = { { 0, 0, 0, 1 }, {0, 0, 0, 1} };
	int dx1, dx3, dy;
	int Dx1, Dx3, Dy;
	float Line1[N][M] = { { 0, 0, 0, 1 }, {0, 0, 0, 1} }, Line2[N][M] = { {0, 0, 0, 1 }, {0, 0, 0, 1} }, Line3[N][M] = { { 0, 0, 0, 1 }, {0, 0, 0, 1} };
	float Line4[N][M] = { { 0, 0, 0, 1 }, {0, 0, 0, 1 } }, Line5[N][M] = { { 0, 0, 0, 1 }, {0, 0, 0, 1} }, Line6[N][M] = { { 0, 0, 0, 1 },
	{0, 0, 0, 1} };
	float cut_points[3][3];
	line1[0][0] = line3[1][0] = line4[0][0] = xA;
	line1[0][1] = line3[1][1] = line4[0][1] = yA;
	line1[0][2] = line3[1][2] = line4[0][2] = zA;
	line1[1][0] = line2[0][0] = line5[0][0] = xB;
	line1[1][1] = line2[0][1] = line5[0][1] = yB;
	line1[1][2] = line2[0][2] = line5[0][2] = zB;
	line2[1][0] = line3[0][0] = line6[0][0] = xC;
	line2[1][1] = line3[0][1] = line6[0][1] = yC;
	line2[1][2] = line3[0][2] = line6[0][2] = zC;
	line4[1][0] = line5[1][0] = line6[1][0] = xV;
	line4[1][1] = line5[1][1] = line6[1][1] = yV;
	line4[1][2] = line5[1][2] = line6[1][2] = zV;

	Line1[0][0] = Line3[1][0] = Line4[0][0] = xa;
	Line1[0][1] = Line3[1][1] = Line4[0][1] = ya;
	Line1[0][2] = Line3[1][2] = Line4[0][2] = za;
	Line1[1][0] = Line2[0][0] = Line5[0][0] = xb;
	Line1[1][1] = Line2[0][1] = Line5[0][1] = yb;
	Line1[1][2] = Line2[0][2] = Line5[0][2] = zb;
	Line2[1][0] = Line3[0][0] = Line6[0][0] = xc;
	Line2[1][1] = Line3[0][1] = Line6[0][1] = yc;
	Line2[1][2] = Line3[0][2] = Line6[0][2] = zc;
	Line4[1][0] = Line5[1][0] = Line6[1][0] = xv;
	Line4[1][1] = Line5[1][1] = Line6[1][1] = yv;
	Line4[1][2] = Line5[1][2] = Line6[1][2] = zv;

	if (Init())
	{
		bool quit = false;
		SDL_Event ever;
		std::cout << "---------------------------------------------------------" << std::endl;
		std::cout << "Operations:\nMove:\nW - up\nA - left\nS - down\nD - right\nV - from user\nB - to user \nRotate:\nQ - clockwise OZ\tE - anticloclwise OZ\nR - clockwise OY\tT - anticloclwise OY\nF - clockwise OX\tG - anticloclwise OX\nScale:\n+ - increase\t- - decrease\n" << std::endl;
		std::cout << "---------------------------------------------------------" << std::endl;
		std::cout << "\nz = " << (line1[0][2] + line2[0][2] + line3[0][2] + line4[0][2]) / 4 << std::endl;

		
		while (!quit)
		{
			while (SDL_PollEvent(&ever) != 0)
				if (ever.type == SDL_QUIT)
					quit = true;
	
			Dx1 = Line1[1][0] - Line1[0][0];
			Dy = Line5[1][1] - Line5[0][1];
			Dx3 = Line3[1][0] - Line3[0][0];
			if (_kbhit())
				switch (_getch()) 
				{
				case 'w':
					up(line1, line2, line3, line4, line5, line6);
					up(Line1, Line2, Line3, Line4, Line5, Line6);
					break;
				case 's':
					down(line1, line2, line3, line4, line5, line6);
					down(Line1, Line2, Line3, Line4, Line5, Line6);
					break;
				case 'a':
					left(line1, line2, line3, line4, line5, line6);
					left(Line1, Line2, Line3, Line4, Line5, Line6);
					break;
				case 'd':
					right(line1, line2, line3, line4, line5, line6);
					right(Line1, Line2, Line3, Line4, Line5, Line6);
					break;
				case 'v':
					fromUser(line1, line2, line3, line4, line5, line6);
					fromUser(Line1, Line2, Line3, Line4, Line5, Line6);
					std::cout << "\n\t\t\tz = " << (line1[0][2] + line2[0][2]
						+ line3[0][2] + line4[0][2]) / 4 << std::endl;
					break;
				case 'b':
					toUser(line1, line2, line3, line4, line5, line6);
					toUser(Line1, Line2, Line3, Line4, Line5, Line6);
					std::cout << "\n\t\t\tz = " << (line1[0][2] + line2[0][2]
						+ line3[0][2] + line4[0][2]) / 4 << std::endl;
					break;
				case 'f':
					rotateX(Line1, Line2, Line3, Line4, Line5, Line6, line1, line2, line3, line4, line5, line6, 1 * angle);
					break;
				case 'g':
					rotateX(Line1, Line2, Line3, Line4, Line5, Line6, line1, line2, line3, line4, line5, line6, -1 * angle);
					break;
				case 'q':
					rotateZ(Line1, Line2, Line3, Line4, Line5, Line6, line1, line2, line3, line4, line5, line6, 1 * angle);
					break;
				case 'e':
					rotateZ(Line1, Line2, Line3, Line4, Line5, Line6, line1, line2, line3, line4, line5, line6, -1 * angle);
					break;
				case 'r':
					rotateY(Line1, Line2, Line3, Line4, Line5, Line6, line1, line2, line3, line4, line5, line6, 1 * angle);
					break;
				case 't':
					rotateY(Line1, Line2, Line3, Line4, Line5, Line6, line1, line2, line3, line4, line5, line6, -1 * angle);
					break;
				case '=':
					scaling(Line1, Line2, Line3, Line4, Line5, Line6, line1, line2, line3, line4, line5, line6, S);
					break;
				case '-':
					scaling(Line1, Line2, Line3, Line4, Line5, Line6, line1, line2, line3, line4, line5, line6, s);
					break;
				}
			SDL_SetRenderDrawColor(Render, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(Render);
			shadow(line1, line2, line3, line4, line5, line6);//тень для первой фигуры
			shadow(Line1, Line2, Line3, Line4, Line5, Line6);//тень для второй фигуры
			paintOver(line1, line2, line3, line4, line5, line6, Line1, Line2, Line3, Line4, Line5, Line6);
			SDL_SetRenderDrawColor(Render, 255, 255, 255, 0x00);
			SDL_RenderPresent(Render);
		}
	}
	else
	{
		std::cout << SDL_GetError() << std::endl;
	}
	return 0;
}
