#define _USE_MATH_DEFINES
#include <iostream> 
#include <iomanip>
#include <string>
#include <cmath> 
using namespace std;

//Класс для поиска величин и синусов углов треугольника
class Angle
{
protected:
	double angle_grad, angle_min;
public:
	void angle_grad_min(double an_g, double an_m)
	{
		angle_grad = an_g;
		angle_min = an_m;
	}
	double angle()
	{
		return angle_grad + (angle_min / 60);
	}
	double Angle_3(double angle_1, double angle_2)
	{
		double angle_g, angle_m, angle;
		int grad = 0;
		//Обработка градусов
		angle_g = angle_1 + angle_2;
		angle_m = (angle_g - int(angle_g)) * 60;
		if ((angle_m <= 60) && (angle_m != 0))
		{
			angle_m = (60 - angle_m);
			grad++;
		}
		else if (angle_m > 60)
		{
			grad = (angle_m) / 60;
			angle_m = angle_m - 60 * grad;
			grad++;
		}
		angle = (180 - grad - int(angle_g)) + (angle_m) / 60;
		angle_grad = int(angle);
		angle_min = (angle - int(angle)) * 60;
		return angle;
	}
	//Получение синуса
	double GetSin(double angle)
	{
		//Перевод в радианы
		double rad;
		rad = (angle * M_PI) / 180;
		return sin(rad);
	}
	//Определение типа треугольника
	void TypeTrian(string& type, int angle_1,
		int angle_2, int angle_3)
	{
		int meter = 0;
		if ((angle_1 == 90) || (angle_2 == 90) || (angle_3 == 90))
		{
			type = "right - angled ";
			meter++;
		}
		else if ((angle_1 == angle_2) || (angle_2 == angle_3))
		{
			type = "isosceles triangle";
			meter++;
			if ((angle_1 == angle_2) &&
				(angle_1 == angle_3) &&
				(angle_2 == angle_3))
			{
				type = "equilateral(3 sides)";
				meter++;
			}
		}
		if (meter == 2)
			type = "equilateral(3 sides) \nisosceles(2 sides)";
		if (meter == 0)
			type = "";
	}
};

//Класс для поиска величин треугольника
class Triangle
{
	Angle angle_1, angle_2, angle_3;
protected:
	double side_a, side_b, side_c;
public:
	//Считывание данных с клавиатуры
	void Read(double& an_g_1, double& an_m_1,
		double& an_g_2, double& an_m_2)
	{
		cin >> side_a >> an_g_1 >> an_m_1 >> an_g_2 >> an_m_2;
		angle_1.angle_grad_min(an_g_1, an_m_1);
		angle_2.angle_grad_min(an_g_2, an_m_2);
		//system("cls");
	}
	//Проверка введенных данных
	bool Init(int angle_grad_1, int angle_min_1,
		int angle_grad_2, int angle_min_2)
	{
		if (
			(side_a <= 0) ||
			((angle_grad_1 < 0) || (angle_grad_1 >= 180)) ||
			((angle_grad_2 < 0) || (angle_grad_2 >= 180)) ||
			((angle_min_1 < 0) || (angle_min_1 > 59)) ||
			((angle_min_2 < 0) || (angle_min_2 > 59)) ||
			((angle_grad_1 + angle_grad_2) >= 180)
			)
		{
			cout << "No" << endl;
			return false;
		}
		else return true;
	}
	//Непосредственный процесс вычисления всех данных
	//Стороны треугольника
	void Sides()
	{
		double
			angle1 = angle_1.angle(),
			angle2 = angle_2.angle(),
			angle3;
		angle3 = angle_3.Angle_3(angle1, angle2);
		side_b = side_a * angle_2.GetSin(angle2) /
			angle_3.GetSin(angle3);
		side_c = side_a * angle_1.GetSin(angle1) /
			angle_3.GetSin(angle3);
	}
	//Площадь треугольника
	double Square(double& square)
	{
		double
			angle1 = angle_1.angle(),
			angle2 = angle_2.angle(),
			angle3 = angle_3.angle();
		square = (pow(side_a, 2) / 2) *
			(angle_1.GetSin(angle1) *
				angle_2.GetSin(angle2) /
				angle_3.GetSin(angle3));
		return round(square * 1000) / 1000;
	}
	//Высоты треугольника
	void Heights(double& h1, double& h2, double& h3, double sq)
	{
		h1 = sq * 2 / side_a;
		h2 = sq * 2 / side_b;
		h3 = sq * 2 / side_c;
	}
	//Периметр треугольника
	void Perimeter(double& perimeter)
	{
		perimeter = side_a + side_b + side_c;
	}
	//Тип треугольника
	string TypeTriangle(string& type)
	{
		double
			angle1 = angle_1.angle(),
			angle2 = angle_2.angle(),
			angle3 = angle_3.angle();
		angle_1.TypeTrian(type, angle1, angle2, angle3);
		return type;
	}
	//Вывод на экран
	void Display(double h1, double h2, double h3,
		double per, double sq, string type)
	{
		double angle1 = angle_1.angle(),
			angle2 = angle_2.angle(),
			angle3 = angle_3.angle();

		cout << "sides " << fixed << setprecision(3)
			<< side_a << " "
			<< side_c << " "
			<< side_b << endl;

		cout << "angles " << setprecision(0)
			<< int(angle3) << " grad "
			<< (angle3 - int(angle3)) * 60 << " min "
			<< int(angle1) << " grad "
			<< (angle1 - int(angle1)) * 60 << " min "
			<< int(angle2) << " grad "
			<< (angle2 - int(angle2)) * 60 << " min "
			<< endl;

		cout << "heights " << setprecision(3)
			<< h1 << " " << h3 << " " << h2 << endl;

		cout << "perimeter= " << fixed << setprecision(3) << per
			<< " square= " << sq << endl;

		cout << type << endl;
	}
};

int main()
{
	static Triangle analys;
	int n;
	double
		angle_grad_1, angle_min_1,
		angle_grad_2, angle_min_2,
		square, perimeter,
		h1, h2, h3;
	string type;
	bool trigger;
	analys.Read(angle_grad_1, angle_min_1,
		angle_grad_2, angle_min_2);
	trigger = analys.Init(angle_grad_1, angle_min_1,
		angle_grad_2, angle_min_2);
	if (trigger == true)
	{
		analys.Sides();
		analys.Square(square);
		analys.Heights(h1, h2, h3, square);
		analys.Perimeter(perimeter);
		analys.TypeTriangle(type);
		analys.Display(h1, h2, h3, perimeter, square, type);
	}
	cin >> n;
	Triangle* mass = new Triangle[n];
	for (int i = 0; i < n; i++)
	{
		mass[i].Read(angle_grad_1, angle_min_1,
			angle_grad_2, angle_min_2);
		trigger = mass[i].Init(angle_grad_1, angle_min_1,
			angle_grad_2, angle_min_2);
		if (trigger == true)
		{
			mass[i].Sides();
			mass[i].Square(square);
			mass[i].Heights(h1, h2, h3, square);
			mass[i].Perimeter(perimeter);
			mass[i].TypeTriangle(type);
			mass[i].Display(h1, h2, h3, perimeter, square, type);
		}
	}
}
