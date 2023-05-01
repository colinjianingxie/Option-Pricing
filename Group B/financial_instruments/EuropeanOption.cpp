/*
* EuropeanOption.cpp
* Defines the EuropeanOption class methods
*/


// Standard Libraries
#include <sstream>
#include <stdlib.h>
#include <string>
#include <iostream>

// Custom header
#include "Option.hpp"
#include "EuropeanOption.hpp"
#include "OptionConstants.hpp"

using namespace std;

namespace Colin {
	namespace FinancialInstruments {

		EuropeanOption::EuropeanOption(): Option::Option() {}
		EuropeanOption::EuropeanOption(OptionType t, double ap, double sp, double ttm, double rf, double vol, double cc): Option::Option(t, ap, sp, ttm, rf, vol, cc){}

		EuropeanOption::EuropeanOption(const EuropeanOption& eo): Option::Option(eo) {}
		EuropeanOption::~EuropeanOption() {}

		EuropeanOption& EuropeanOption::operator = (const EuropeanOption& source)
		{
			if (this == &source) // if current address is the same as source's address
			{
				return *this; // return current object (avoid assignment on itself)
			}
			Option::operator=(source);
			return *this; // return current object's pointer
		}

		// Returns the class of option
		OptionClass EuropeanOption::option_class() const
		{
			return European;
		}

		// Returns custom theoretical price, derived from Option class
		double EuropeanOption::theoretical_price() const
		{
			return calculate_theoretical_price(
				this->option_type(), 
				this->time_to_maturity(), 
				this->strike_price(), 
				this->volatility(), 
				this->current_price(), 
				this->risk_free_rate(), 
				this->cost_of_carry()
			);
		}


		// overloading << Operator for printing out European Option as String
		ostream& operator << (ostream& os, const EuropeanOption& eo)
		{
			string optionType;
			optionType = eo.option_type();
			os << "\nEuropean Option (" << optionType << "):" << endl; // We can access private elements due to friend
			os << "Price: " << eo.current_price() << endl;
			os << "Strike: " << eo.strike_price() << endl;
			os << "Time to Maturity: " << eo.time_to_maturity() << endl;
			os << "Volatility: " << eo.volatility() << endl;
			os << "Theoretical Price: " << eo.theoretical_price() << endl;
			return os; // display the Option
		}
		
	}
}