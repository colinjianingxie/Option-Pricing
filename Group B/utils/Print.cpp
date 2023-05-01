/*
* Print.cpp
* Provides global functions for pritning
*/

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "Print.hpp"

using namespace std;

namespace Colin {
	namespace Utils {

		// Function that prints a vector of doubles
		void print(vector<double> v)
		{
			cout << "[";
			for (int i = 0; i < v.size()-1; i++) // Iterate through all values of the vector
			{
				cout << v[i] << ", "; // Print each value
			}
			cout << v[v.size() - 1] << "]" << endl; // end with bracket
		}

		// Function that prints matrix of doubles
		void print(vector<vector<double>> v)
		{
			for (int i = 0; i < v.size(); i++)
			{
				cout << "[";
				for (int j = 0; j < v[0].size()-1; j++)
				{
					cout << v[i][j] << ", ";
				}
				cout << v[i][v[0].size() - 1] << "]" << endl;
			}


		}
	}
}

