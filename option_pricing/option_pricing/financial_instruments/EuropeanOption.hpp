/*
* EuropeanOption.hpp
* Provides template methods for European Options
*/
#ifndef EUROPEAN_OPTION_HPP // Verify we have unique HPP file reference
#define EUROPEAN_OPTION_HPP // Name the file EUROPEAN_OPTION_HPP

#include <string>
#include <iostream>


// Custom HPP files
#include "Option.hpp"
#include "OptionConstants.hpp"
#include "OptionParameter.hpp"
#include "OptionFormulas.hpp"

using namespace std;

namespace Colin {
	namespace FinancialInstruments {
		class EuropeanOption: public Option
		{
		public:
			EuropeanOption(); // Default constructor: initializes a default European Option

			// Constructor according to Black-Scholes formula 
			EuropeanOption(OptionType t, double ap, double sp, double ttm, double rf, double vol, double cc);  

			EuropeanOption(const EuropeanOption& eo);  // Copy constructor for European Option
			~EuropeanOption(); // Destructor: called when European Option

			// Operators
			EuropeanOption& operator = (const EuropeanOption& source); // Assignment operator.

			//bool valid_option(const EuropeanOption& eo) const; // Returns if the two options have valid put call parity

			OptionClass option_class() const; // Returns class of option

			// Calculates the European Theoretical Price according to Black-Scholes option model
			double theoretical_price() const;

			// String Methods
			friend ostream& operator << (ostream& os, const EuropeanOption& eo); // overloading << Operator for printing out EuropeanOption as String

		private:


		};
	}
}
#endif // !EUROPEAN_OPTION_HPP
