/*
* OptionManager.cpp
* Defines the OptionManager class methods
*/


// Standard Libraries
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cmath>
#include <map>
#include <vector>


// Custom header
#include "EuropeanOption.hpp"
#include "OptionConstants.hpp"
#include "OptionParameter.hpp"
#include "OptionManager.hpp"

using namespace std;

namespace Colin {
	namespace FinancialInstruments {


		OptionManager::OptionManager(){}
		

		OptionManager::OptionManager(const OptionManager& eo){}
		OptionManager::~OptionManager() {}

		OptionManager& OptionManager::operator = (const OptionManager& source)
		{
			if (this == &source) // if current address is the same as source's address
			{
				return *this; // return current object (avoid assignment on itself)
			}
			return *this; // return current object's pointer
		}
		

		vector<double> OptionManager::calculate_parameter(Option& o, OptionFunctionType oft, OptionParameter& op)
		{
			vector<double> result;
			double original_value = o.get(op.type()); // get original value

			for (int i = 0; i < op.values().size(); i++)
			{
				o.set_parameter(op.type(), op.get(i)); // Set new parameter
				result.push_back(o.calculate(oft)); // Obtain each new price and append to end of result
			}
			o.set_parameter(op.type(), original_value); // reset value for option

			return result;
		}


		vector<vector<double>> OptionManager::matrix_pricer(Option& o, OptionFunctionType oft, vector<OptionParameter> parameter_vector)
		{
			// Map is used to restore parameters at end

			map<OptionParameterType, double> original_parameters;
			vector<double> result_prices; // Column vector for resulting prices after parameter changes

			// Note: We assume user provides same size parameter vectors
			size_t number_parameters = parameter_vector.size(); // Number of option parameters
			size_t number_values_per_parameter = parameter_vector[0].size(); // Choose arbitrary parameter and get number of values inside
			for (int i = 0; i < number_values_per_parameter; i++) // i = index of value per option parameter
			{
				for (int j = 0; j < number_parameters; j++) // j = index of the current parameter type
				{
					OptionParameterType adjustType = parameter_vector[j].type(); // Get current parameter		
					double adjustValue = parameter_vector[j].get(i); // the ith element of the values inside the parameter being tuned

					if (i == 0) // First time iterating through values, store all the original parameters
					{
						original_parameters[adjustType] = o.get(adjustType); // Get original parameter value and save it
					}

					o.set_parameter(adjustType, adjustValue); // Change the parameter of the option
				}
				// After adjusting all the parameters, calculate the price
				result_prices.push_back(o.calculate(oft)); // Append the new calculated price
			}

			// Reset all the parameters back to orignal values
			for (int j = 0; j < number_parameters; j++)
			{
				OptionParameterType tempType = parameter_vector[j].type(); // get the changed parameter
				o.set_parameter(tempType, original_parameters[tempType]); // reset the changed parameter
			}
			return vector<vector<double>>{ result_prices }; // Return matrix of the prices
		}

	}
}