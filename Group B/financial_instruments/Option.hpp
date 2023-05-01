/*
* Option.hpp
* Provides template methods for Options
*/

#ifndef OPTION_HPP // Verify we have unique HPP file reference
#define OPTION_HPP // Name the file OPTION_HPP

#include <string>
#include <iostream>

// Custom HPP files
#include "OptionConstants.hpp"
#include "OptionParameter.hpp"

using namespace std;

namespace Colin {
	namespace FinancialInstruments {
		class Option
		{
		public:
			Option(); // Default Constructor for option
			Option(OptionType t, double ap, double sp, double ttm, double rf, double vol, double cc);
			Option(OptionType t, double ap, double sp, double rf, double vol, double cc);
			Option(const Option& o);  // copy constructor for Option
			virtual ~Option(); // Destructor: called when Option object gets removed from memory

			// Operators
			Option& operator = (const Option& source); // Assignment operator.

			// Setter Methods
			void set_parameter(OptionParameterType opt, double value); // Sets the parameter given with value
			static void set_h(double val); // sets the error for approximating

			// Getter Methods
			double get(OptionParameterType opt) const; // Obtain value based on option parameter type
			static double get_h();  // gets the error for approximating
			double calculate(OptionFunctionType oft) const; // Calculates the theoretical values based on what type of function type

			int id() const; // getter method to return the ID
			virtual OptionClass option_class() const = 0;
			double time_to_maturity() const; // exercise (maturity) date 
			double strike_price() const; // Strike Price of option
			double volatility() const; // Constant volatility
			double current_price() const; // Asset Price
			double risk_free_rate() const; // Risk free interest Rate
			double cost_of_carry() const; // Cost of Carry
			OptionType option_type() const; // Type of option (put or call)
			OptionType complement_option_type() const; // Complement of Option

			virtual double theoretical_price() const = 0; // Gets price of option 
			double delta() const; // Gets delta of option
			double gamma() const; // Gets gamma of option
			double vega() const; // Gets vega of option
			double theta() const; // Gets theta of option
			double approximate_delta() const; // Approximates the delta value, given a small h value
			double approximate_gamma() const; // Approximates the gamma value, given a small h value

			double parity_price() const; // Gets the price of the opposite option based on put call parity

			// String methods

		private:
			int m_id; // id for each option, could be used eventually if making a trading system to track trades

			double T; // Time to maturity
			double K; // Strike price
			double sig; // volatility
			double S; // current stock price
			double r; // risk free rate
			OptionType type; // either call or put
			double b; // cost of carry parameter

			static double h; // default gap for approximating greeks
		};
	}
}
#endif // !OPTION_HPP
