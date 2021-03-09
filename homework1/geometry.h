#pragma once
#include <cmath>

const double ER = 1e-9;
const double pi = 3.1415926535;

class Point {
private:
    int x_, y_;

public:
    Point(int a = 0, int b = 0) :
        x_(a), y_(b)
    {}

    Point(const Point& other) {
        x_ = other.x_;
        y_ = other.y_;
    }

    double getX() const { return x_; }
    void setX(int x) { x_ = x; return; }

    double getY() const { return y_; }
    void setY(int y) { y_ = y; return; }

    Point& operator=(const Point& other) {
        if (this == &other)
            return *this;

        x_ = other.x_;
        y_ = other.y_;
        return *this;
    }
};

class PolygonalChain {
protected:
    Point* arrayOfPoints_;
    size_t size_;

public:
    PolygonalChain(size_t size = 0, Point* mas = nullptr) {
        size_ = size;
        arrayOfPoints_ = new Point[size];
        for (size_t i = 0; i < size; i++)
            arrayOfPoints_[i] = mas[i];
    }

    PolygonalChain(const PolygonalChain& other) {
        size_ = other.size_;
        arrayOfPoints_ = new Point[size_];
        for (size_t i = 0; i < size_; i++)
            arrayOfPoints_[i] = other.arrayOfPoints_[i];
    }

    virtual  ~PolygonalChain() {
        delete[] arrayOfPoints_;
    }

    int getN() const { return size_; }
    Point getPoint(int n) const { return arrayOfPoints_[n]; }

    virtual double perimeter() const {
        double p = 0;
        for (size_t i = 0; i < size_ - 1; i++)
            p += sqrt((arrayOfPoints_[i].getX() - arrayOfPoints_[i + 1].getX())
                * (arrayOfPoints_[i].getX() - arrayOfPoints_[i + 1].getX())
                + (arrayOfPoints_[i].getY() - arrayOfPoints_[i + 1].getY())
                * (arrayOfPoints_[i].getY() - arrayOfPoints_[i + 1].getY()));
        return p;
    }

    PolygonalChain& operator=(const PolygonalChain& other) {
        if (this == &other)
            return *this;

        size_ = other.size_;
        for (size_t i = 0; i < size_; i++)
            arrayOfPoints_[i] = other.arrayOfPoints_[i];
        return *this;
    }
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    //fixed constructor from base class
    ClosedPolygonalChain(size_t size = 0, Point* arrayOfPoints = nullptr) :
        PolygonalChain(size, arrayOfPoints)
    {}

    double perimeter() const {
        return PolygonalChain::perimeter() + sqrt((arrayOfPoints_[0].getX() - arrayOfPoints_[size_ - 1].getX())
            * (arrayOfPoints_[0].getX() - arrayOfPoints_[size_ - 1].getX())
            + (arrayOfPoints_[0].getY() - arrayOfPoints_[size_ - 1].getY())
            * (arrayOfPoints_[0].getY() - arrayOfPoints_[size_ - 1].getY()));
    }
};

class Polygon : public ClosedPolygonalChain {
public:
    Polygon(size_t n = 0, Point* arrayOfPoints = nullptr) :
        ClosedPolygonalChain(n, arrayOfPoints)
    {}

    virtual double area() const {
        double a = 0;
        for (size_t i = 0; i < size_ - 1; i++)
            a += arrayOfPoints_[i].getX() * arrayOfPoints_[i + 1].getY();
        double b = 0;
        for (size_t i = 0; i < size_ - 1; i++)
            b += arrayOfPoints_[i + 1].getX() * arrayOfPoints_[i].getY();

        return abs((a - b) / 2);
    }
};

class Triangle : public Polygon {
public:
    Triangle(int n, Point* arrayOfPoints) :
        Polygon(n, arrayOfPoints)
    {}

    //fixed without sqrt
    bool hasRightAngle() const {
        double a = (arrayOfPoints_[0].getX() - arrayOfPoints_[1].getX())
            * (arrayOfPoints_[0].getX() - arrayOfPoints_[1].getX())
            + (arrayOfPoints_[0].getY() - arrayOfPoints_[1].getY())
            * (arrayOfPoints_[0].getY() - arrayOfPoints_[1].getY());
        double b = (arrayOfPoints_[0].getX() - arrayOfPoints_[2].getX())
            * (arrayOfPoints_[0].getX() - arrayOfPoints_[2].getX())
            + (arrayOfPoints_[0].getY() - arrayOfPoints_[2].getY())
            * (arrayOfPoints_[0].getY() - arrayOfPoints_[2].getY());
        double c = (arrayOfPoints_[1].getX() - arrayOfPoints_[2].getX())
            * (arrayOfPoints_[1].getX() - arrayOfPoints_[2].getX())
            + (arrayOfPoints_[1].getY() - arrayOfPoints_[2].getY())
            * (arrayOfPoints_[1].getY() - arrayOfPoints_[2].getY());
        //fixed you have constant
        //fixed return expression
        return (abs(a + b - c) <= ER
            || abs(b + c - a) <= ER
            || abs(c * c + a - b) <= ER);
    }
};

class Trapezoid : public Polygon {
public:
    Trapezoid(int n, Point* arrayOfPoints) :
        Polygon(n, arrayOfPoints)
    {}

    double height() const {
        double b, d;
        b = sqrt((arrayOfPoints_[1].getX() - arrayOfPoints_[2].getX())
            * (arrayOfPoints_[1].getX() - arrayOfPoints_[2].getX())
            + (arrayOfPoints_[1].getY() - arrayOfPoints_[2].getY())
            * (arrayOfPoints_[1].getY() - arrayOfPoints_[2].getY()));
        d = sqrt((arrayOfPoints_[3].getX() - arrayOfPoints_[0].getX())
            * (arrayOfPoints_[3].getX() - arrayOfPoints_[0].getX())
            + (arrayOfPoints_[3].getY() - arrayOfPoints_[0].getY())
            * (arrayOfPoints_[3].getY() - arrayOfPoints_[0].getY()));
        double med = (b + d) / 2;
        return this->area() / med;
    }
};
//fixed area and perimeter
class RegularPolygon : public Polygon {
public:
    RegularPolygon(int n, Point* arrayOfPoints) :
        Polygon(n, arrayOfPoints)
    {}

    double area() {
        double side = sqrt((arrayOfPoints_[0].getX() - arrayOfPoints_[1].getX())
            * (arrayOfPoints_[0].getX() - arrayOfPoints_[1].getX())
            + (arrayOfPoints_[0].getY() - arrayOfPoints_[1].getY())
            * (arrayOfPoints_[0].getY() - arrayOfPoints_[1].getY()));
        return (size_ * side * side) / (4 * tan(pi / size_));
    }

    double perimeter() {
        double side = sqrt((arrayOfPoints_[0].getX() - arrayOfPoints_[1].getX())
            * (arrayOfPoints_[0].getX() - arrayOfPoints_[1].getX())
            + (arrayOfPoints_[0].getY() - arrayOfPoints_[1].getY())
            * (arrayOfPoints_[0].getY() - arrayOfPoints_[1].getY()));
        return size_ * side;
    }
};
