/*
* Print.hpp
* Provides global functions for pritning
*/
#ifndef PRINT_HPP // Verify we have unique HPP file reference
#define PRINT_HPP // Name the file PRINT_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

namespace Colin {
	namespace Utils {
		void print(vector<double> v);
		void print(vector<vector<double>> v);
	}
}
#endif // !PRINT_HPP
