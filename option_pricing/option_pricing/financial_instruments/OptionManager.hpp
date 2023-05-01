/*
* OptionManager.hpp
* Provides template methods for Option Manager
*/
#ifndef OPTION_MANAGER_HPP // Verify we have unique HPP file reference
#define OPTION_MANAGER_HPP // Name the file OPTION_MANAGER_HPP

#include <string>
#include <iostream>
#include <vector>

// Boost libraries


// Custom HPP files
#include "OptionConstants.hpp"
#include "OptionParameter.hpp"
#include "Option.hpp"

using namespace std;

namespace Colin {
	namespace FinancialInstruments {
		class OptionManager
		{
		public:

			OptionManager();
			OptionManager(const OptionManager& eo);  // Copy constructor for European Option
			~OptionManager(); // Destructor: called when European Option

			// Operators
			OptionManager& operator = (const OptionManager& source); // Assignment operator.

			vector<double> calculate_parameter(Option& o, OptionFunctionType oft, OptionParameter& op); // 
			vector<vector<double>> matrix_pricer(Option& o, OptionFunctionType oft, vector<OptionParameter> parameter_vector); // Returns grid of theoretial values based on a vector of Option Parameters and Type of function


		private:


		};
	}
}
#endif // !OPTION_MANAGER_HPP
