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

double Round(double dVal, short iPlaces) {
	double dRetval = 0;
	double dMod = 0.0000001;
	if (dVal < 0.0) dMod = -0.0000001;
	dRetval = dVal;
	dRetval += (5.0 / pow(10.0, iPlaces + 1.0));
	dRetval *= pow(10.0, iPlaces);
	dRetval = floor(dRetval + dMod);
	dRetval /= pow(10.0, iPlaces);
	return(dRetval);
}


void Intersect::addCmd(string text)
{
	string buf1, buf2, buf3, buf4, buf5;
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0, r = 0;
	stringstream s(text);
	s >> buf1 >> buf2 >> buf3 >> buf4 >> buf5;
	if (buf1.at(0) == 'L') {
		x1 = stoi(buf2);
		y1 = stoi(buf3);
		x2 = stoi(buf4);
		y2 = stoi(buf5);
		this->addLine(x1, y1, x2, y2);
	}
	else if (buf1.at(0) == 'C') {
		x1 = stoi(buf2);
		y1 = stoi(buf3);
		r = stoi(buf4);
		this->addCircle(x1, y1, r);
	}
	
}

void Intersect::addCircle(int x, int y, int r)
{
	unique_ptr<Circle> circle = make_unique<Circle>();
	//Circle *circle = new Circle();
	circle->x = x;
	circle->y = y;
	circle->r = r;
	circles.push_back(*circle);
	/*
	circles[size_of_circles].x = x;
	circles[size_of_circles].y = y;
	circles[size_of_circles].r = r;
	size_of_circles++;
	*/
}

void Intersect::addLine(int x1, int y1, int x2, int y2)
{
	double dy = 0, dx = 0;
	dy = static_cast<double>(y1) - static_cast<double>(y2);
	dx = static_cast<double>(x1) - static_cast<double>(x2);
	unique_ptr<Line> line = make_unique<Line>();
	//Line *line = new Line();
	line->x1 = x1;
	line->y1 = y1;
	line->x2 = x2;
	line->y2 = y2;
	
	
	line->k = dy / dx;
	line->b = - line->k * x1 + y1;
	lines.push_back(*line);
	/*
	lines[size_of_lines].x1 = x1;
	lines[size_of_lines].y1 = y1;
	lines[size_of_lines].x2 = x2;
	lines[size_of_lines].y2 = y2;
	lines[size_of_lines].k = dy / dx;
	lines[size_of_lines].b = lines[size_of_lines].k * x1 + y1;
	size_of_lines++;
	*/
}

void Intersect::intersect2lines(Line line1, Line line2)
{
	double  k1 = 0, b1 = 0, k2 = 0, b2 = 0, x = 0, y = 0;

	k1 = line1.k;
	b1 = line1.b;
	k2 = line2.k;
	b2 = line2.b;

	if (k1 == k2) {
		return;
	}

	unique_ptr<IntersectPoint> intersectpoint = make_unique<IntersectPoint>();
	//IntersectPoint *intersectpoint = new IntersectPoint();
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
	const double x1 = static_cast<double>(circle1.x);
	const double y1 = static_cast<double>(circle1.y);
	const double x2 = static_cast<double>(circle2.x);
	const double y2 = static_cast<double>(circle2.y);
	const double r1 = static_cast<double>(circle1.r);
	const double r2 = static_cast<double>(circle2.r);
	const double k = -(x2 - x1) / (y2 - y1);
	const double b = (((r1 * r1 - r2 * r2) - (-x1 - x2) *(x2 - x1)) / (y2 - y1) + y1 + y2) / 2;
	Line l;
	l.k = k;
	l.b = b;
	l.x1 = (((r1 * r1 - r2 * r2) - (y1 + y2) *(y2 - y1)) / (x1 - x2) + x1 + x2) / 2;
	l.x2 = l.x1;
	intersectLine2circle(l, circle1);
}

void Intersect::intersectLine2circle(Line line, Circle circle)
{
	const double k = line.k;
	const double b = line.b;
	const double x1 = circle.x;
	const double y1 = circle.y;
	const double r= circle.r;
	if (isinf(k)) {
		const double ans_x1 = line.x1;
		const double d = r * r - (ans_x1 - x1) * (ans_x1 - x1);
		if (d >= 0) {
			const double ans_y1 = y1 + sqrt(d);
			const double ans_y2 = y1 - sqrt(d);
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
		const double a = 1 + k * k;
		const double b2 = -2 * x1 + 2 * k * b - 2 * k * y1;
		const double c = x1 * x1 + b * b + y1 * y1 - 2 * b * y1 - r * r;
		const double d = b2 * b2 - 4 * a * c;
		if (d >= 0) {
			const double ans_x1 = (-b2 + sqrt(d)) / (2 * a);
			const double ans_y1 = ans_x1 * k + b;
			const double ans_x2 = (-b2 - sqrt(d)) / (2 * a);
			const double ans_y2 = ans_x2 * k + b;
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
	double x = Round(intersectpoint.x,10);
	double y = Round(intersectpoint.y,10);
	intersectpoints.insert(pair<double, double>(x, y));
}

int Intersect::intersect()
{
	const unsigned int lines_size = lines.size();
	const unsigned int circles_size = circles.size();
	for (unsigned int i = 0;lines_size != 0 && i < lines_size - 1;i++) {
		const Line line = lines.at(i);
		for (unsigned int j = i + 1;j < lines_size; j++) {
			intersect2lines(line, lines.at(j));
		}
	}
	for (unsigned int i = 0; circles_size != 0 && i < circles_size - 1; i++) {
		const Circle circle = circles.at(i);
		for (unsigned int j = i + 1; j < circles_size; j++) {
			intersect2circles(circle, circles.at(j));
		}
	}
	for (unsigned int i = 0;i < lines_size; i++) {
		const Line line = lines.at(i);
		for (unsigned int j = 0; j < circles_size; j++) {
			intersectLine2circle(line, circles.at(j));
		}
	}
	/*
	for (int i = 0; size_of_lines != 0 && i < size_of_lines - 1; i++) {
		for (int j = i + 1; j < size_of_lines; j++) {
			intersect2lines(lines[i], lines[j]);
		}
	}
	for (int i = 0; size_of_circles != 0 && i < size_of_circles - 1; i++) {
		for (int j = i + 1; j < size_of_circles; j++) {
			intersect2circles(circles[i], circles[j]);
		}
	}
	for (int i = 0; i < size_of_lines; i++) {
		for (int j = 0; j < size_of_circles; j++) {
			intersectLine2circle(lines[i], circles[j]);
		}
	}
	*/
	//printIntersectPoint();
	return intersectpoints.size();
}

void Intersect::printIntersectPoint()
{
	ofstream out("points.txt");
	for (auto p : intersectpoints) {
		cout << p.first << " " << p.second << endl;
		out << p.first << " " << p.second << endl;
	}

}

int main(int argc, char **argv)
{
	int num = 0;
	Intersect intersect;
	const int test = 0;
	if (test) {
		intersect.addLine(0, 0, 0, 1);
		num = 5000;
		for (int i = 0; i < num; i++) {
			intersect.addLine(0, i, 1, i);
		}
		for (int i = 0; i < num; i++) {
			intersect.addCircle(i, 0, 1);
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
	else if(argc == 5){
		string infile = string(argv[2]);
		string outfile = string(argv[4]);
		ifstream in(infile);
		ofstream out(outfile);
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
		//intersect.printIntersectPoint();
	}
}

