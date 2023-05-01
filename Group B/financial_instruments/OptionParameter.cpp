/*
* OptionParameter.cpp
* Defines the OptionParameter class methods
*/


// Standard Libraries
#include <sstream>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

// Custom header
#include "OptionConstants.hpp"
#include "OptionParameter.hpp"

using namespace std;

namespace Colin {
	namespace FinancialInstruments {
		

		OptionParameter::OptionParameter(): parameter_type(StrikePrice), parameter_values(vector<double>{0}) {}
		OptionParameter::OptionParameter(OptionParameterType t): parameter_type(t), parameter_values(vector<double>{0}){}
		OptionParameter::OptionParameter(OptionParameterType t, vector<double> values) : parameter_type(t), parameter_values(values) {}
		OptionParameter::OptionParameter(OptionParameterType t, double start, double end, double mesh_size): parameter_type(t)
		{
			double h = (end - start) / mesh_size;
			for (int i = 0; i <= mesh_size; i++)
			{
				parameter_values.push_back(start + h * i);
			}
		}
		OptionParameter::OptionParameter(const OptionParameter& op) : parameter_type(op.parameter_type), parameter_values(op.parameter_values){}
		OptionParameter::~OptionParameter() {}

		OptionParameter& OptionParameter::operator = (const OptionParameter& source)
		{
			if (this == &source) // if current address is the same as source's address
			{
				return *this; // return current object (avoid assignment on itself)
			}
			parameter_type = source.parameter_type;
			for (int i = 0; i < source.parameter_values.size(); i++)
			{
				parameter_values.push_back(source.parameter_values[i]);
			}

			return *this; // return current object's pointer
		}

		OptionParameterType OptionParameter::type() const
		{
			return parameter_type;
		}

		vector<double> OptionParameter::values() const
		{
			return parameter_values;
		}

		double OptionParameter::get(int idx) const
		{
			return parameter_values[idx];
		}

		size_t OptionParameter::size() const
		{
			return parameter_values.size();
		}

	}
}