#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <utility>

using namespace std;

class Line {
public:
	int x1;
	int x2;
	int y1;
	int y2;
	double k;
	double b;
};

class IntersectPoint {
public:
	double x = 0;
	double y = 0;
};

class Intersect {
private:
	vector<Line> lines;
	//unordered_map<pair<double, double>, IntersectPoint> *intersectpoints = new unordered_map<pair<double, double>, IntersectPoint>();
	set<pair<double, double>> intersectpoints;

public:
	void addLine(int x1, int y1, int x2, int y2);
	void intersect2lines(Line line1, Line line2);
	void addIntersectPoint(IntersectPoint intersectpoint);
	int intersect();
};