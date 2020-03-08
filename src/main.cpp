// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include "main.h"
#include <exception>
#include <set>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;




void Intersect::addLine(int x1, int y1, int x2, int y2)
{
	Line *line = new Line();
	line->x1 = x1;
	line->y1 = y1;
	line->x2 = x2;
	line->y2 = y2;
	double dy, dx;
	dy = (double)y1 - (double)y2;
	dx = (double)x1 - (double)x2;
	line->k = dy / dx;
	line->b = - line->k * x1 + y1;
	lines.push_back(*line);
}

void Intersect::intersect2lines(Line line1, Line line2)
{
	double  k1, b1, k2, b2, x, y;

	k1 = line1.k;
	b1 = line1.b;
	k2 = line2.k;
	b2 = line2.b;

	if (k1 == k2) {
		return;
	}

	IntersectPoint *intersectpoint = new IntersectPoint();
	if (isinf(k1) && isinf(k2)) {
		return;
	}
	else if (isinf(k1)) {
		x = line1.x1;
		y = k2 * x + b2;
	}
	else if (isinf(k2)) {
		x = line2.x1;
		y = k1 * x + b1;
	}
	else {
		x = -(b1 - b2) / (k1 - k2);
		if (isnan(x) || isinf(x)) {
			return;
		}
		else {
			y = k1 * x + b1;
		}
	}
	intersectpoint->x = x;
	intersectpoint->y = y;
	addIntersectPoint(*intersectpoint);
	return;
}

void Intersect::addIntersectPoint(IntersectPoint intersectpoint)
{
	/*
	unsigned int k;
	for (k = 0; k < intersectpoints.size(); k++) {
		IntersectPoint ip2 = intersectpoints[k];
		if (ip2.x == intersectpoint.x && ip2.y == intersectpoint.y) {
			break;
		}
	}
	if (k == intersectpoints.size()) {
		intersectpoints.push_back(intersectpoint);
	}
	*/
	intersectpoints.insert(pair<double,double>(intersectpoint.x, intersectpoint.y));
	//intersectpoints->insert({ pair<double, double>(intersectpoint.x, intersectpoint.y), intersectpoint });
}

int Intersect::intersect()
{
	if (lines.size() == 0) {
		return 0;
	}
	for (unsigned int i = 0;i < lines.size() - 1;i++) {
		for (unsigned int j = i + 1;j < lines.size(); j++) {
			intersect2lines(lines[i], lines[j]);
		}
	}
	return intersectpoints.size();
}

int main(int argc, char **argv)
{
	int num;
	Intersect intersect;
	int test = 0;
	int x1, x2, y1, y2;
	char c;
	if (test) {
		intersect.addLine(0, 0, 0, 1);
		num = 5000;
		for (int i = 0; i < num; i++) {
			intersect.addLine(0, i, 1, i);
		}
		cout << intersect.intersect();
		return 0;
	}
	if (argc < 2) {
		cin >> num;
		for (int i = 0; i < num; i++) {
				
			cin >> c;
			cin >> x1;
			cin >> y1;
			cin >> x2;
			cin >> y2;
			intersect.addLine(x1, y2, x2, y2);
		}
		cout << intersect.intersect();
	}
	else {
		ifstream in(argv[2]);
		ofstream out(argv[4]);
		string text;
		if (!in)
		{
			cout << "文件打开失败！" << argv[2] << endl;
			exit(1);
		}
		getline(in, text);
		num = stoi(text);
		for (int i = 0; i < num; i++) {
			getline(in, text);
			string buf1, buf2, buf3, buf4, buf5;
			stringstream s(text);
			s >> buf1 >> buf2 >> buf3 >> buf4 >> buf5;
			x1 = stoi(buf2);
			y1 = stoi(buf3);
			x2 = stoi(buf4);
			y2 = stoi(buf5);
			intersect.addLine(x1, y1, x2, y2);
		}
		//cout << intersect.intersect();
		out << intersect.intersect();
	}
}

