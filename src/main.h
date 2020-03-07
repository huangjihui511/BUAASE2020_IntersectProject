#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Line {
public:
	int x1;
	int x2;
	int y1;
	int y2;
};

class IntersectPoint {
public:
	double x = 0;
	double y = 0;
};

class Intersect {
private:
	vector<Line> lines;
	vector<IntersectPoint> intersectpoints;

public:
	void addLine(int x1, int y1, int x2, int y2);
	IntersectPoint intersect2lines(Line line1, Line line2);
	int intersect();
};