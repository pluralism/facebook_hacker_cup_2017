#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream fin("progress_pie.txt");
	ofstream fout;
	fout.open("result.txt", ofstream::out | ostream::app);
	int T;
	fin >> T;
	auto is_inside([](auto x, auto y) { return pow(x - 50, 2) + pow(y - 50, 2) <= pow(50, 2); });
	auto angle([](auto x, auto y) { return atan2(x - 50, y - 50) / (2 * M_PI); });
	for(auto i = 0; i < T; i++)
	{
		int p, x, y;
		fin >> p >> x >> y;
		auto angle_point = angle(x, y);
		if (angle_point < 0) angle_point++;
		fout << "Case #" << i + 1 << ": " << (is_inside(x, y) && angle_point * 100 <= p ? "black" : "white") << '\n';
	}
	return 0;
}
