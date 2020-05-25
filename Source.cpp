#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cmath>
using namespace std;

struct coor { 
	double x;
	double y;
};

void rec_polygon(coor* ver, int k, int* xmax, int* xmin, int* ymax, int* ymin);
void input_points(coor* points, int n, int xmax, int xmin, int ymax, int ymin);
double x_cross(double y, double x1, double y1, double x2, double y2);
int random(int a, int b);
void print_points(coor* points_inside, int n1, int n);
bool if_inside_polygon(double x, double y, coor* a, int num);
bool if_inside_ellipse(double x, double y, int n, int a, int b);
bool if_inside_ring(double x, double y, int n, double r1, double r2);
int okrug(double a);
int getint(char* X);
void first_quadrant(coor* ver, int* xmax, int* xmin, int* ymax, int* ymin, int k);

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	int n;						// ���-�� ��������� �����
	int n1 = 0;					// ���-�� �����, ������� ������ ��������������
	int xmax, xmin, ymax, ymin; // ����������� ������� (�������������)
	double w;
	system("cls");

	if (!strcmp(argv[1],"ellipse")) {
		double a, b;			//�������
		n = getint(argv[2]);	//���-�� �����
		cout << "������� �������: "; cin >> a;
		cout << "����� �������: "; cin >> b;
		xmax = 2*a; xmin = 0; ymax = 2*b; ymin = 0;

		coor* points = new coor[n]; // ������ ���� �����
		coor* points_inside = new coor[n]; // ������ �����, �������� ��������

		input_points(points, n, xmax, xmin, ymax, ymin);
		for (int i = 0; i < n; i++) {
			if (if_inside_ellipse(points[i].x, points[i].y, n, a, b)) {
				points_inside[n1].x = points[i].x;
				points_inside[n1].y = points[i].y;
				n1++;
			}
		}

		for (int i = 0; i < n1; i++) {
			points_inside[i].x = points_inside[i].x * (80.0 / xmax);
			points_inside[i].y = points_inside[i].y * (50.0 / ymax);
		}

		print_points(points_inside, n1, n);

		w = ((xmax - xmin) * (ymax - ymin)) * n1 / (n * 1.0);
		printf("������� ~= %lf\n", w);
		delete[] points_inside;
		delete[] points;
	}

	else if (!strcmp(argv[1], "ring")) {
		n = getint(argv[2]);
		double r1, r2;
		cout << "������ ������� ����������: "; cin >> r1;
		cout << "������ ������� ����������: "; cin >> r2;
		xmax = 2*r1; xmin = 0; ymax = 2*r1; ymin = 0;

		coor* points = new coor[n]; // ������ ���� �����
		coor* points_inside = new coor[n]; // ������ �����, �������� ��������

		input_points(points, n, xmax, xmin, ymax, ymin);

		for (int i = 0; i < n; i++) {
			if (if_inside_ring(points[i].x, points[i].y, n, r1, r2)) {
				points_inside[n1].x = points[i].x;
				points_inside[n1].y = points[i].y;
				n1++;
			}
		}

		for (int i = 0; i < n1; i++) {
			points_inside[i].x = points_inside[i].x * (80.0 / xmax);
			points_inside[i].y = points_inside[i].y * (50.0 / ymax);
		}

		cout << endl;
		print_points(points_inside, n1, n);

		w = ((xmax - xmin) * (ymax - ymin)) * n1 / (n * 1.0);
		printf("������� ~= %lf\n", w);
		delete[] points_inside;
		delete[] points;
	}
	
	else if (!strcmp(argv[1], "polygon")) {
		int k;				// ���-�� ���� � ������
		n = getint(argv[2]);

		printf("���-�� ������ ��������������: "); scanf_s("%d", &k);

		coor* ver = new coor[k]; // ������ ��������� ������

		printf("���������� ������ �������������� � ������� (x,y):\n");
		for (int i = 0; i < k; i++) {
			printf("%d: ", i); scanf_s("%lf%lf", &ver[i].x, &ver[i].y);
		}

		rec_polygon(ver, k, &xmax, &xmin, &ymax, &ymin);
//		cout << "xmax = " << xmax << ", xmin = " << xmin << ", ymax = " << ymax << ", ymin = " << ymin << endl;

		coor* points = new coor[n];			// ������ ���� �����
		coor* points_inside = new coor[n];	// ������ �����, �������� ��������

		input_points(points, n, xmax, xmin, ymax, ymin);

		for (int i = 0; i < n; i++) {
			if (if_inside_polygon(points[i].x, points[i].y, ver, k)) {
				points_inside[n1].x = points[i].x;
				points_inside[n1].y = points[i].y;
				n1++;
			}
		}

		first_quadrant(ver, &xmax, &xmin, &ymax, &ymin, k);
		for (int i = 0; i < n1; i++) {
			points_inside[i].x = points_inside[i].x * (80.0 / xmax);
			points_inside[i].y = points_inside[i].y * (50.0 / ymax);
		}

		cout << endl;
		print_points(points_inside, n1, n);

		w = ((xmax - xmin) * (ymax - ymin)) * n1 / (n * 1.0);
		cout << "n = " << n << ", n1 = " << n1 << endl;
		printf("������� ~= %lf\n", w);
		
		delete[] points_inside;
		delete[] points;
		delete[] ver;
	}

	else if (!strcmp(argv[1], "random_polygon")) {
		n = getint(argv[2]);
		int len = 80;					// "�����" ��������������
		int minv = getint(argv[3]);
		int maxv = getint(argv[4]);
		int k = random(minv, maxv);;		// ���-�� ���� � ������
		coor mas[1000];
		int z = 0;
		double x = 0;
		double y;
		int q = 0;
		bool f;
		double dx = len / (k * 1.0);

		while (z < 3) {
			z = 0; q = 0;
			for (int i = 0; i < k; i++) {
				f = random(0, 1);
				if (f) {
					mas[q].x = dx * i * 1.0;
					mas[q].y = random(0, 50) + random(0,100)/(100.0);
					q++; z++;
				}
			}
			for (int j = 0; j < k; j++) {
				f = random(0, 1);
				if (f) {
					mas[q].x = len - dx * j * 1.0;
					mas[q].y = random(-50, 0) + random(0,100)/(100.0);
					q++; z++;
				}
			}

		}
		k = z;

		coor* ver = new coor[k]; // ������ ��������� ������

		for (int i = 0; i < z; i++) {
			ver[i].x = mas[i].x;
			ver[i].y = mas[i].y;
		}

		rec_polygon(ver, k, &xmax, &xmin, &ymax, &ymin);

		coor* points = new coor[n]; // ������ ���� �����
		coor* points_inside = new coor[n]; // ������ �����, �������� ��������

		first_quadrant(ver, &xmax, &xmin, &ymax, &ymin, k);
		input_points(points, n, xmax, xmin, ymax, ymin);

		for (int i = 0; i < n; i++) {
			if (if_inside_polygon(points[i].x, points[i].y, ver, k)) {
				points_inside[n1].x = points[i].x;
				points_inside[n1].y = points[i].y;
				n1++;
			}
		}

		for (int i = 0; i < n1; i++) {
			points_inside[i].x = points_inside[i].x * (80.0 / xmax);
			points_inside[i].y = points_inside[i].y * (50.0 / ymax);
		}

		print_points(points_inside, n1, n);
		cout << endl;
		w = ((xmax - xmin) * (ymax - ymin)) * n1 / (n * 1.0);
		cout << "n = " << n << ", n1 = " << n1 << endl;
		cout << "n1/n = " << n1 / (n * 1.0) << endl;
		printf("������� ~= %lf\n", w);
		delete[] points_inside;
		delete[] points;
		delete[] ver;

	}


	return 0;
}

// ��������� �����
void print_points(coor* points_inside, int n1, int n) {
	//80x50
	int w, e;
	const int X = 80;
	const int Y = 50;
	int paint[Y][X];

	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			paint[i][j] = 0;
		}
	}

	for (int i = 0; i < n1; i++) {
		w = okrug(points_inside[i].x);
		e = okrug(points_inside[i].y);
		if (w == 80) continue;
		if (e == 50) continue;
		paint[e][w]++;
	}
	cout << endl;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = Y - 1; i >= 0; i--) {
		for (int j = 0; j < X; j++) {
			if (paint[i][j] == 0) SetConsoleTextAttribute(hConsole, 0);
			else if (paint[i][j] < 0.0001666 * n) SetConsoleTextAttribute(hConsole, 8);
			else if (paint[i][j] < 0.0003333 * n) SetConsoleTextAttribute(hConsole, 7);
			else SetConsoleTextAttribute(hConsole, 15);
			cout << 'o';
		}
		cout << endl;
	}
	SetConsoleTextAttribute(hConsole, 15);
}

// ������� ���� ������ � ������ ��������
void first_quadrant(coor* ver, int* xmax, int* xmin, int* ymax, int* ymin, int k) {
	if (*xmin < 0) {
		for (int i = 0; i < k; i++) {
			ver[i].x = ver[i].x + abs(*xmin);
		}
		*xmax = *xmax + abs(*xmin);
		*xmin = 0;
	}

	if (*ymin < 0) {
		for (int i = 0; i < k; i++) {
			ver[i].y = ver[i].y + abs(*ymin);
		}
		*ymax = *ymax + abs(*ymin);
		*ymin = 0;
	}
}

// ������� ��������� �������� int �� char
int getint(char* X) {
	int k = strlen(X);
	int i = 0;
	bool f = false;
	int n = 0;
	int number;
	if (X[0] == '-') {
		f = true;
		i = 1;
		k--;
	}
	for (int j = 0; j < k; j++) {
		number = (int)X[i] - 48;
		n = n + number * pow(10, k - j - 1);
		i++;
	}
	if (f) n = 0 - n;
	return n;
}

// ����������
int okrug(double a) {
	int b = (int)a;
	if (a - b < 0.5) return b;
	else return b + 1;
}

// ��������� ����� �� ��������� (a;b)
int random(int a, int b) {
	return rand() % (b - a + 1) + a;
}

// ��������� ������ � �������������� � ���� int
void rec_polygon(coor* ver, int k, int* xmax, int* xmin, int* ymax, int* ymin) {
	double xmax1 = ver[0].x, xmin1 = ver[0].x, ymax1 = ver[0].y, ymin1 = ver[0].y;
	for (int i = 1; i < k; i++) {
		if (ver[i].x > xmax1) xmax1 = ver[i].x;
		if (ver[i].x < xmin1) xmin1 = ver[i].x;
		if (ver[i].y > ymax1) ymax1 = ver[i].y;
		if (ver[i].y < ymin1) ymin1 = ver[i].y;
	}
	if ((int)xmax1 != xmax1) {
		if (xmax1 > 0) *xmax = (int)xmax1 + 1;
		else *xmax = (int)xmax1 - 1;
	}
	else *xmax = (int)xmax1;
	if ((int)xmin1 != xmin1) {
		if (xmin1 > 0) *xmin = (int)xmin1 + 1;
		else *xmin = (int)xmin1 - 1;
	}
	else *xmin = (int)xmin1;
	if ((int)ymax1 != ymax1) {
		if (ymax1 > 0) *ymax = (int)ymax1 + 1;
		else *ymax = (int)ymax1 - 1;
	}
	else *ymax = (int)ymax1;
	if ((int)ymin1 != ymin1) {
		if (ymin1 > 0) *ymin = (int)ymin1 + 1;
		else *ymin = (int)ymin1 - 1;
	}
	else *ymin = (int)ymin1;
}

// ���������� ������� ���������� �������
void input_points(coor* points, int n, int xmax, int xmin, int ymax, int ymin) {
	double q;
	for (int i = 0; i < n; i++) {
		do {
			q = rand() % (99 - 0 + 1) + 0; //������� ����� ���������� ����� (�����)
			points[i].x = rand() % (xmax - xmin + 1) + xmin + q / 100 * 1.0;
		} while (points[i].x > xmax);
		do {
			q = rand() % (99 - 0 + 1) + 0;
			points[i].y = rand() % (ymax - ymin + 1) + ymin + q / 100 * 1.0;
		} while (points[i].y > ymax);
	}
}

// �������� �� �������������� ����� ��������������
bool if_inside_polygon(double x, double y, coor* a, int num) {
	double q;
	int i, j;
	int count, ct;
	int h, l, r;		//��������������� ����������

	//�������� �������������� ����� ����� �� ������ ��-��
	count = 1;
	for (i = 1; i <= num; i++) { //���������, ����� �� ������ ����� �� �����-������ �� ������ ��������������
		if (i == num) j = 1;
		else j = i + 1;

		//��������, ����� �� ������ ����� �� ������� ��� ������ �� ��� �����������
		if (((x - a[j].x) * (a[i].y - a[j].y)) == ((y - a[j].y) * (a[i].x - a[j].x))) {
			if (((a[i].x < a[j].x) && (a[i].x <= x) && (x <= a[j].x)) || ((a[i].x > a[j].x) && (a[j].x <= x) && (x <= a[i].x))) {
				count = 0;
				break;
			}
		}
	}

	//���� ������ ����� �� ����� �� �� ����� ������� ��������������, �� ��������� ���������		
	if (count) {
		//�������� ������ || ox	

		ct = 0;			//�������, � ������� ������������ ���-�� ����������� �������������� �����
		for (i = 1; i <= num; i++) {	//���������� ������ ������� ��-��

			if (i == num) j = 1;
			else j = i + 1;

			//���������, ���������� �� ������ ������� (�������)
			if (((y - a[i].y) * (y - a[j].y)) < 0)
			{	//"<" ��������, ��� �� �� ����� ������, ����� ������ �������� ����� ����� �������

				//�������� � ����� ������� �����
				if (x < ((y - a[i].y) * (a[j].x - a[i].x) / (a[j].y - a[i].y) + a[i].x))
				{
					ct++; //���� ������ - ����������� ������� �� �������
				}
			}
			//���� ������ ������� ����� �� ����
			else if ((a[i].y == a[j].y) && (y == a[i].y))
			{
				if (i == 1)	l = num;
				else l = i - 1;
				if (i == num - 1) r = 1;
				else r = j + 1;
				//���� \_   ���  _/ , �� ��������� � �������� �������
				//       \      /     
				//                _
				//���� \_/  ���  / \ , �� ��������� � �������� ������
				if (((y - a[l].y) * (y - a[r].y)) < 0)
				{
					ct++;
				}
				else if (((y - a[l].y) * (y - a[r].y)) > 0)
				{
					ct += 2;
				}
			}
			//���� �� ������ �������� ����� ����� �������, ����� 
			//���������, ��� ����������� ������� ������������ ������ �����
			else if (y == a[i].y)
			{
				if (i == 1)	h = num;
				else h = i - 1;

				//���� ������� �����������:
				//  \ ��� /
				//  /     \ ,�� ���������� � �������� �������

				//���� ������� �����������:
				//  \/  ��� /\ ,
				//�� ���������� � �������� ������

				if (((y - a[h].y) * (y - a[j].y)) < 0) ct++;

				else if (((y - a[h].y) * (y - a[j].y)) > 0)	ct += 2;
			}
		}
		if (ct % 2 == 0) return 0;	//���� ������ ���-�� ����������� ���� � ��-���, �� ����� �������
		else return 1;
	}
	return 1;
}

bool if_inside_ellipse(double x, double y, int n, int a, int b) {
	if ((x-a) * (x-a) / (a * a * 1.0) + (y-b) * (y-b) / (b * b * 1.0) <= 1) return 1;
	return 0;
}

bool if_inside_ring(double x, double y, int n, double r1, double r2) {
	if ((x-r1)*(x-r1) + (y-r1)*(y-r1) <= r1*r1 && (x-r1)*(x-r1) + (y-r1)*(y-r1) >= r2*r2) return 1;
	return 0;
}