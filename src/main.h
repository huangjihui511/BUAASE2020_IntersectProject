#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <utility>

using namespace std;

class Line {
public:
	double x1;
	double x2;
	double y1;
	double y2;
	double k;
	double b;
};

class IntersectPoint {
public:
	double x = 0;
	double y = 0;
};

class Circle {
public:
	int r;
	int x;
	int y;
};

class Intersect {
private:
	vector<Line> lines;
	vector<Circle> circles;
	//unordered_map<pair<double, double>, IntersectPoint> *intersectpoints = new unordered_map<pair<double, double>, IntersectPoint>();
	set<pair<double, double>> intersectpoints;

public:
	void addCmd(string s);
	void addCircle(int x, int y, int r);
	void addLine(int x1, int y1, int x2, int y2);
	void intersect2lines(Line line1, Line line2);
	void intersect2circles(Circle circle1, Circle circle2);
	void intersectLine2circle(Line line, Circle circle);
	void addIntersectPoint(IntersectPoint intersectpoint);
	int intersect();
};