/*
* AmericanPerpetualOption.cpp
* Defines the AmericanOption class methods
*/


// Standard Libraries
#include <sstream>
#include <stdlib.h>
#include <string>
#include <iostream>

// Custom header
#include "Option.hpp"
#include "AmericanPerpetualOption.hpp"
#include "OptionConstants.hpp"

using namespace std;

namespace Colin {
	namespace FinancialInstruments {

		AmericanPerpetualOption::AmericanPerpetualOption() : Option::Option() {} // Default constructor
		AmericanPerpetualOption::AmericanPerpetualOption(OptionType t, double ap, double sp, double rf, double vol, double cc) : Option::Option(t, ap, sp, rf, vol, cc) {} // Custom constructor for passed in parameters

		AmericanPerpetualOption::AmericanPerpetualOption(const AmericanPerpetualOption& eo) : Option::Option(eo) {} // Copy constructor
		AmericanPerpetualOption::~AmericanPerpetualOption() {} // Destructor

		AmericanPerpetualOption& AmericanPerpetualOption::operator = (const AmericanPerpetualOption& source)
		{
			if (this == &source) // if current address is the same as source's address
			{
				return *this; // return current object (avoid assignment on itself)
			}
			Option::operator=(source);
			return *this; // return current object's pointer
		}

		// Returns type of option class
		OptionClass AmericanPerpetualOption::option_class() const
		{
			return American;
		}

		// Returns custom theoretical price, derived from Option class
		double AmericanPerpetualOption::theoretical_price() const
		{
			return calculate_american_perpetual_theoretical_price(
				this->option_type(),
				this->strike_price(), 
				this->volatility(), 
				this->current_price(), 
				this->risk_free_rate(), 
				this->cost_of_carry()
			);
		}


		// overloading << Operator for printing out American Option as String
		ostream& operator << (ostream& os, const AmericanPerpetualOption& eo)
		{
			string optionType;
			optionType = eo.option_type();
			os << "\nAmerican Option (" << optionType << "):" << endl; // We can access private elements due to friend
			os << "Price: " << eo.current_price() << endl;
			os << "Strike: " << eo.strike_price() << endl;
			os << "Time to Maturity: " << eo.time_to_maturity() << endl;
			os << "Volatility: " << eo.volatility() << endl;
			os << "Theoretical Price: " << eo.theoretical_price() << endl;
			return os; // display the Option
		}

	}
}