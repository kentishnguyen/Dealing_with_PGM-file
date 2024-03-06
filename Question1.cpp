#include <iostream>

using namespace std;

class BasicShape
{
private:
	double area;
public:
	double getArea()
	{
		return area;
	}
	virtual void calcArea() = 0;
	void setArea(double a)
	{
		area = a;
	}

};

class Circle : public BasicShape
{
private: 
	long  centerX, centerY;
	double radius;
public:
	Circle(long  x, long  y, double r) : centerX(x), centerY(y), radius(r)
	{
		calcArea();
	}
	long  getCenterX()
	{
		return centerX;
	}
	long  getCenterY()
	{
		return centerY;
	}
	void calcArea()
	{
		cout << "> Circle calc called" << endl;
		double temp = 3.14159 * radius * radius;
		BasicShape::setArea(temp);
	}
};

class Rectangle : public BasicShape
{
private:
	long  width, length;
public:
	Rectangle(long  w, long  len) : width(w), length(len)
	{
		calcArea();
	}
	long  getWidth()
	{
		return width;
	}
	long  getLength()
	{
		return length;
	}
	void calcArea()
	{
		cout << "> Rectangle calc called" << endl;
		double temp = length * width;
		BasicShape::setArea(temp);
	}
};

class Square : public Rectangle
{
private:
	long sideLength;
public: 
	Square(long side) : Rectangle(side, side), sideLength(side)
	{
		calcArea();
	}
	long getSideLength()
	{
		return sideLength;
	}
	void calcArea()
	{
		cout << "> Square calc called" << endl;
		double temp = sideLength * sideLength;
		BasicShape::setArea(temp);
	}
};

int main()
{
	Circle c(3,4,5);
	Square s(5);
	Rectangle r(4, 5);
	c.calcArea();
	cout << "> This is the are of the circle object: " << c.getArea() << endl;
	s.calcArea();
	cout << "> This is the are of the square object: " << s.getArea() << endl;
	r.calcArea();
	cout << "> This is the are of the rectangle object: " << r.getArea() << endl;

	return 0;
}