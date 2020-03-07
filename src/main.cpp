// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include "main.h"
#include <exception>

using namespace std;




void Intersect::addLine(int x1, int y1, int x2, int y2)
{
	Line line;
	line.x1 = x1;
	line.y1 = y1;
	line.x2 = x2;
	line.y2 = y2;
	lines.push_back(line);
}

IntersectPoint Intersect::intersect2lines(Line line1, Line line2)
{
	double dy = 0, dx, k1, b1, k2, b2, x, y;
	dy = (double)line1.y1 - (double)line1.y2;
	dx = (double)line1.x1 - (double)line1.x2;
	k1 = dy / dx;
	b1 = -k1 * line1.x1 + line1.y1;
	dy = (double)line2.y1 - (double)line2.y2;
	dx = (double)line2.x1 - (double)line2.x2;
	k2 = dy / dx;
	b2 = -k2 * line2.x1 + line2.y1;
	IntersectPoint *intersectpoint = new IntersectPoint();
	if (isinf(k1) && isinf(k2)) {
		throw exception();
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
			throw exception();
		}
		else {
			y = k1 * x + b1;
		}
	}
	intersectpoint->x = x;
	intersectpoint->y = y;
	return *intersectpoint;
}

int Intersect::intersect()
{
	if (lines.size() == 0) {
		return 0;
	}
	for (unsigned int i = 0;i < lines.size() - 1;i++) {
		for (unsigned int j = i + 1;j < lines.size(); j++) {
			try {
				IntersectPoint ip = intersect2lines(lines[i], lines[j]);
				unsigned int k;
				for (k = 0; k < intersectpoints.size(); k++) {
					IntersectPoint ip2 = intersectpoints[k];
					if (ip2.x == ip.x && ip2.y == ip.y) {
						break;
					}
				}
				if (k == intersectpoints.size()) {
					intersectpoints.push_back(ip);
				}
			}
			catch (exception) {
				;
			}
		}
	}
	return intersectpoints.size();
}

int main()
{
	int num;
	Intersect intersect;
	/*
	cin >> num;
	for (int i = 0; i < num; i++) {
		int x1, x2, y1, y2;
		char c;
		cin >> c;
		cin >> x1;
		cin >> y1;
		cin >> x2;
		cin >> y2;
		intersect.addLine(x1, y2, x2, y2);
	}
	*/

	intersect.addLine(0, 0, 0, 1);
	num = 5000;
	for (int i = 0; i < num; i++) {
		intersect.addLine(0, i, 1, i);
	}

	cout << intersect.intersect();
}

