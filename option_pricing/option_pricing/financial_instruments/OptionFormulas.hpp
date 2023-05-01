/*
* Formulas.hpp
* Provides template methods for all of Option Formulas
*/
#ifndef OPTION_FORMULAS_HPP // Verify we have unique HPP file reference
#define OPTION_FORMULAS_HPP // Name the file OPTION_FORMULAS_HPP

#include <string>
#include <iostream>

#include "OptionConstants.hpp"
#include "Option.hpp"

using namespace std;

namespace Colin {
    namespace FinancialInstruments {
        /*
			double T; // Time to maturity
			double K; // Strike price
			double sig; // volatility
			double S; // current stock price
			double r; // risk free rate
			OptionType type; // either call or put
			double b; // cost of carry parameter
        */
		double calculate_american_perpetual_theoretical_price(OptionType type, double K, double sig, double S, double r, double b); // Returns american perpetual theoretical price
        double calculate_theoretical_price(OptionType type, double T, double K, double sig, double S, double r, double b); // Returns european theoretical price
		double calculate_delta(OptionType type, double T, double K, double sig, double S, double r, double b); // returns delta of option
		double calculate_gamma(OptionType type, double T, double K, double sig, double S, double r, double b); // returns gamma of option
		double calculate_vega(OptionType type, double T, double K, double sig, double S, double r, double b); // returns vega of option
		double calculate_theta(OptionType type, double T, double K, double sig, double S, double r, double b); // returns theta of option
		double calculate_delta_approximation(OptionType type, double T, double K, double sig, double S, double r, double b, double h); // returns delta approximation
		double calculate_gamma_approximation(OptionType type, double T, double K, double sig, double S, double r, double b, double h); // returns gamma approximation

		double N(double val); // Returns CDF of given value
		double n(double val); // Returns PDF of given value
		double d1(double S, double K, double sig, double T, double b); // term used for black scholes
		double d2(double d1, double sig, double T); // term used for black scholes

		bool have_same_option_values(Option& a, Option& b); // checks if two options have same values
		bool check_put_call_parity(Option& a, Option& b); // checks if two options have put call parity

		

    }
}
#endif // !OPTION_FORMULAS_HPP
