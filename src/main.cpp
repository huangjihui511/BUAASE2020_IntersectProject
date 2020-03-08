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




void Intersect::addCmd(string text)
{
	string buf1, buf2, buf3, buf4, buf5;
	int x1, x2, y1, y2, r;
	stringstream s(text);
	s >> buf1 >> buf2 >> buf3 >> buf4 >> buf5;
	if (buf1[0] == 'L') {
		x1 = stoi(buf2);
		y1 = stoi(buf3);
		x2 = stoi(buf4);
		y2 = stoi(buf5);
		this->addLine(x1, y1, x2, y2);
	}
	else if (buf1[0] == 'C') {
		x1 = stoi(buf2);
		y1 = stoi(buf3);
		r = stoi(buf4);
		this->addCircle(x1, y1, r);
	}
	
}

void Intersect::addCircle(int x, int y, int r)
{
	Circle *circle = new Circle();
	circle->x = x;
	circle->y = y;
	circle->r = r;
	circles.push_back(*circle);
}

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

void Intersect::intersect2circles(Circle circle1, Circle circle2)
{
	double x1 = (double)circle1.x;
	double y1 = (double)circle1.y;
	double x2 = (double)circle2.x;
	double y2 = (double)circle2.y;
	double r1 = (double)circle1.r;
	double r2 = (double)circle2.r;
	double k = -(x2 - x1) / (y2 - y1);
	double b = (((r1 * r1 - r2 * r2) - (-x1 - x2) *(x2 - x1)) / (y2 - y1) + y1 + y2) / 2;
	Line l;
	l.k = k;
	l.b = b;
	l.x1 = (((r1 * r1 - r2 * r2) - (y1 + y2) *(y2 - y1)) / (x1 - x2) + x1 + x2) / 2;
	l.x2 = l.x1;
	intersectLine2circle(l, circle1);
}

void Intersect::intersectLine2circle(Line line, Circle circle)
{
	double k = line.k;
	double b = line.b;
	double x1 = circle.x;
	double y1 = circle.y;
	double r= circle.r;
	if (isinf(k)) {
		double ans_x1 = line.x1;
		double d = r * r - (ans_x1 - x1) * (ans_x1 - x1);
		if (d >= 0) {
			double ans_y1 = y1 + sqrt(d);
			double ans_y2 = y1 - sqrt(d);
			IntersectPoint i1;
			IntersectPoint i2;
			i1.x = ans_x1;
			i1.y = ans_y1;
			i2.x = ans_x1;
			i2.y = ans_y2;
			addIntersectPoint(i1);
			addIntersectPoint(i2);
		}
	}
	else {
		double a = 1 + k * k;
		double b2 = -2 * x1 + 2 * k * b - 2 * k * y1;
		double c = x1 * x1 + b * b + y1 * y1 - 2 * b * y1 - r * r;
		double d = b2 * b2 - 4 * a * c;
		if (d >= 0) {
			double ans_x1 = (-b2 + sqrt(d)) / (2 * a);
			double ans_y1 = ans_x1 * k + b;
			double ans_x2 = (-b2 - sqrt(d)) / (2 * a);
			double ans_y2 = ans_x2 * k + b;
			IntersectPoint i1;
			IntersectPoint i2;
			i1.x = ans_x1;
			i1.y = ans_y1;
			i2.x = ans_x2;
			i2.y = ans_y2;
			addIntersectPoint(i1);
			addIntersectPoint(i2);
		}
	}
	
}

void Intersect::addIntersectPoint(IntersectPoint intersectpoint)
{

	intersectpoints.insert(pair<double,double>(intersectpoint.x, intersectpoint.y));
}

int Intersect::intersect()
{
	for (unsigned int i = 0;lines.size() != 0 && i < lines.size() - 1;i++) {
		for (unsigned int j = i + 1;j < lines.size(); j++) {
			intersect2lines(lines[i], lines[j]);
		}
	}
	for (unsigned int i = 0; circles.size() != 0 && i < circles.size() - 1; i++) {
		for (unsigned int j = i + 1; j < circles.size(); j++) {
			intersect2circles(circles[i], circles[j]);
		}
	}
	for (unsigned int i = 0;i < lines.size(); i++) {
		for (unsigned int j = 0; j < circles.size(); j++) {
			intersectLine2circle(lines[i], circles[j]);
		}
	}
	return intersectpoints.size();
}

int main(int argc, char **argv)
{
	int num;
	Intersect intersect;
	int test = 0;
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
		cin >> num ;
		while (cin.get() != '\n');
		for (int i = 0; i < num; i++) {
			char buffer[256];
			fgets(buffer, 256, stdin);
			string cmd(buffer);
			intersect.addCmd(cmd);
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
			intersect.addCmd(text);
		}
		//cout << intersect.intersect();
		out << intersect.intersect();
	}
}

