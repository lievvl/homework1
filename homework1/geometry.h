#pragma once
#include <iostream>
#include <cmath>

class Point {
private:
    int x, y;

public:
    Point() {
        this->x = 0;
        this->y = 0;
    }

    Point(int a, int b) {
        this->x = a;
        this->y = b;
    }

    int getX() const { return x; }
    void setX(int a) { x = a; return; }

    int getY() const { return y; }
    void setY(int a) { x = a; return; }

    Point operator= (const Point obj) {
        this->x = obj.x;
        this->y = obj.y;
        return *this;
    }
};

class PolygonalChain {
protected:
    Point* arr;
    int num;

public:
    PolygonalChain() {
        num = 0;
        arr = nullptr;
    }

    PolygonalChain(int n, Point* mas) {
        num = n;
        arr = new Point[n];
        for (int i = 0; i < n; i++)
            arr[i] = mas[i];
    }

    int getN() const { return num; }
    Point getPoint(int n) const { return arr[n]; }

    double perimeter() const {
        double p = 0;
        for (int i = 0; i < num - 1; i++)
            p += sqrt((arr[i].getX() - arr[i + 1].getX()) * (arr[i].getX() - arr[i + 1].getX()) + (arr[i].getY() - arr[i + 1].getY()) * (arr[i].getY() - arr[i + 1].getY()));
        return p;
    }
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain() {
        num = 0;
        arr = nullptr;
    }

    ClosedPolygonalChain(int n, Point* mas) {
        num = n + 1;
        arr = new Point[n + 1];
        for (int i = 0; i < n; i++)
            arr[i] = mas[i];
        arr[n] = mas[0];
    }

    int getN() const { return num - 1; }
};

class Polygon : public ClosedPolygonalChain {
public:
    Polygon() {
        num = 0;
        arr = nullptr;
    }

    Polygon(int n, Point* mas) {
        num = n + 1;
        arr = new Point[n + 1];
        for (int i = 0; i < n; i++)
            arr[i] = mas[i];
        arr[n] = mas[0];
    }

    double area() const {
        int a = 0;
        for (int i = 0; i < num - 2; i++)
            a += arr[i].getX() * arr[i + 1].getY();
        int b = 0;
        for (int i = 0; i < num - 2; i++)
            b += arr[i + 1].getX() * arr[i].getY();

        return abs((a - b) / 2);
    }
};

class Triangle : public Polygon {
public:
    Triangle(int n, Point* mas) {
        num = n + 1;
        arr = new Point[n + 1];
        for (int i = 0; i < n; i++)
            arr[i] = mas[i];
        arr[n] = mas[0];
    }

    bool hasRightAngle() const {
        double a = sqrt((arr[0].getX() - arr[1].getX()) * (arr[0].getX() - arr[1].getX()) + (arr[0].getY() - arr[1].getY()) * (arr[0].getY() - arr[1].getY()));
        double b = sqrt((arr[0].getX() - arr[2].getX()) * (arr[0].getX() - arr[2].getX()) + (arr[0].getY() - arr[2].getY()) * (arr[0].getY() - arr[2].getY()));
        double c = sqrt((arr[1].getX() - arr[2].getX()) * (arr[1].getX() - arr[2].getX()) + (arr[1].getY() - arr[2].getY()) * (arr[1].getY() - arr[2].getY()));
        if (a * a + b * b == c * c || b * b + c * c == a * a || c * c + a * a == b * b)
            return true;
        else
            return false;
    }
};

class Trapezoid : public Polygon {
public:
    Trapezoid(int n, Point* mas) {
        num = n + 1;
        arr = new Point[n + 1];
        for (int i = 0; i < n; i++)
            arr[i] = mas[i];
        arr[n] = mas[0];
    }

    double height() const {
        double b, d;
        b = sqrt((arr[1].getX() - arr[2].getX()) * (arr[1].getX() - arr[2].getX()) + (arr[1].getY() - arr[2].getY()) * (arr[1].getY() - arr[2].getY()));
        d = sqrt((arr[3].getX() - arr[4].getX()) * (arr[3].getX() - arr[4].getX()) + (arr[3].getY() - arr[4].getY()) * (arr[3].getY() - arr[4].getY()));
        double med = (b + d) / 2;
        return this->area() / med;
    }
};

class RegularPolygon : public Polygon {
public:
    RegularPolygon(int n, Point* mas) {
        num = n + 1;
        arr = new Point[n + 1];
        for (int i = 0; i < n; i++)
            arr[i] = mas[i];
        arr[n] = mas[0];
    }
};