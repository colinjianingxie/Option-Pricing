/*
* OptionParameter.hpp
* Provides template methods for Option Parameters
*/
#ifndef OPTION_PARAMETER_HPP // Verify we have unique HPP file reference
#define OPTION_PARAMETER_HPP // Name the file OPTION_PARAMETER_HPP

#include <string>
#include <iostream>
#include <vector>

#include "OptionConstants.hpp"

using namespace std;

namespace Colin {
	namespace FinancialInstruments {
		class OptionParameter
		{
		public:
			OptionParameter(); // Default Constructor
			OptionParameter(OptionParameterType t); // Constructor with only option parameter type
			OptionParameter(OptionParameterType t, vector<double> values); // Constructor with parameter type and doubles
			OptionParameter(OptionParameterType t, double start, double end, double mesh_size); // Constructor for range of values
			OptionParameter(const OptionParameter& op);  // Copy constructor for Option Parameter
			~OptionParameter(); // Destructor: called when Option Parameter

			OptionParameterType type() const; // Returns parameter type
			vector<double> values() const; // Returns parameter values
			double get(int idx) const; // Returns specific value in values
			size_t size() const; // Returns paramter values size
			// Operators
			OptionParameter& operator = (const OptionParameter& source); // Assignment operator.

		private:
			vector<double> parameter_values; // values that will be inputted as parameters with the parameter type
			OptionParameterType parameter_type; // One of the option type parameter enums
		};
	}
}
#endif // !OPTION_PARAMETER_HPP
