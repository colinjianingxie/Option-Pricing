/*
* AmericanPerpetualOption.hpp
* Provides template methods for American Options
*/
#ifndef AMERICAN_PERPETUAL_OPTION_HPP // Verify we have unique HPP file reference
#define AMERICAN_PERPETUAL_OPTION_HPP // Name the file AMERICAN_PERPETUAL_OPTION_HPP

#include <string>
#include <iostream>


// Boost libraries


// Custom HPP files
#include "Option.hpp"
#include "OptionConstants.hpp"
#include "OptionParameter.hpp"
#include "OptionFormulas.hpp"

using namespace std;

namespace Colin {
	namespace FinancialInstruments {
		class AmericanPerpetualOption : public Option
		{
		public:
			AmericanPerpetualOption(); // Default constructor: initializes a default American Option

			// Constructor according to Black-Scholes formula 
			AmericanPerpetualOption(OptionType t, double ap, double sp, double rf, double vol, double cc);

			AmericanPerpetualOption(const AmericanPerpetualOption& ao);  // Copy constructor for American Option
			~AmericanPerpetualOption(); // Destructor: called when American Option

			// Operators
			AmericanPerpetualOption& operator = (const AmericanPerpetualOption& source); // Assignment operator.

			//bool valid_option(const AmericanOption& eo) const; // Returns if the two options have valid put call parity

			OptionClass option_class() const; // Returns class of option

			// Calculates the American Theoretical Price according to Black-Scholes option model
			double theoretical_price() const;

			// String Methods
			friend ostream& operator << (ostream& os, const AmericanPerpetualOption& eo); // overloading << Operator for printing out AmericanOption as String

		private:
		};
	}
}
#endif // !AMERICAN_PERPETUAL_OPTION_HPP
