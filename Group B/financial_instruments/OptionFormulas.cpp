/*
* Formulas.hpp
* Provides implementation for all of Option Formulas
*/
#include <string>
#include <iostream>
#include <cmath>

// Boost Libraries
#include <boost/random/normal_distribution.hpp>
#include<boost/math/distributions.hpp>

#include "OptionConstants.hpp"
#include "OptionFormulas.hpp"
#include "Option.hpp"

using namespace std;

namespace Colin {
    namespace FinancialInstruments {
		
		using namespace boost::math;

		// Calculates american perpetual option price according to literature
		double calculate_american_perpetual_theoretical_price(OptionType type, double K, double sig, double S, double r, double b)
		{
			double temp = b / pow(sig, 2);
			if (type == OptionType::Call)
			{
				double y1 = 0.5 - temp + sqrt(pow(temp - 0.5, 2) + 2 * r / (pow(sig, 2)));
				return (K / (y1 - 1)) * pow((((y1 - 1) / y1) * S / K), y1);
			}
			else if (type == OptionType::Put)
			{
				double y2 = 0.5 - temp - sqrt(pow(temp - 0.5, 2) + 2 * r / (pow(sig, 2)));
				return (K / (1 - y2)) * pow((((y2 - 1) / y2) * S / K), y2);
			}
			return 0;
		}

		// Calculates theoretical european option price according to literature
        double calculate_theoretical_price(OptionType type, double T, double K, double sig, double S, double r, double b)
        {
			double d1_val = d1(S, K, sig, T, b);
			double d2_val = d2(d1_val, sig, T);

			if (type == OptionType::Call) // If option type is call
			{
				return S * exp((b - r) * T) * N(d1_val) - K * exp(-r * T) * N(d2_val); // C = S*e^(bT-rT)*N(d1) - K*e^(-rT)*N(d2)
			}
			else if (type == OptionType::Put) // If option type is put
			{
				return K * exp(-r * T) * N(-d2_val) - S * exp((b - r) * T) * N(-d1_val); // P =  K*e^(-rT)*N(-d2) - S*e^(bT-rT)*N(-d1)
			}
			return 0;
        }

		// Calculates delta according to literature
		double calculate_delta(OptionType type, double T, double K, double sig, double S, double r, double b)
		{

			double d1_val = d1(S, K, sig, T, b);

			if (type == OptionType::Call) // If option type is call
			{
				return exp((b - r) * T) * N(d1_val);
			}
			else if (type == OptionType::Put) // If option type is put
			{
				return exp((b - r) * T) * (N(d1_val) - 1.0);
			}

			return 0.0;
		}

		// Calculates gamma according to literature
		double calculate_gamma(OptionType type, double T, double K, double sig, double S, double r, double b)
		{

			double d1_val = d1(S, K, sig, T, b);

			if (type == OptionType::Call || type == OptionType::Put) // If option type is call or put
			{
				return exp((b - r) * T) * n(d1_val) / (S * sig * sqrt(T));
			}

			return 0.0;
		}
		// Calculates vega according to literature

		double calculate_vega(OptionType type, double T, double K, double sig, double S, double r, double b)
		{
			double d1_val = d1(S, K, sig, T, b);

			if (type == OptionType::Call || type == OptionType::Put) // If option type is call or put
			{
				return S * sqrt(T) * exp((b - r) * T) * n(d1_val);
			}

			return 0.0;
		}

		// Calculates theta according to literature
		double calculate_theta(OptionType type, double T, double K, double sig, double S, double r, double b)
		{
			double d1_val = d1(S, K, sig, T, b);
			double d2_val = d2(d1_val, sig, T);
			double term_1 = (S * sig * exp((b - r) * T) * n(d1_val)) / (2 * sqrt(T));
			double term_2 = (b-r) * S * exp((b - r) * T);
			double term_3 = r * K * exp(-r * T);

			if (type == OptionType::Call) // If option type is call
			{
				return -term_1 - term_2 * N(d1_val) - term_3 * N(d2_val);
			}
			else if (type == OptionType::Put) // If option type is put
			{
				return term_2 * N(-d1_val) + term_3 * N(-d2_val) - term_1;
			}

			return 0.0;
		}

		// Approximates delta greek
		double calculate_delta_approximation(OptionType type, double T, double K, double sig, double S, double r, double b, double h)
		{
			double term_1 = calculate_theoretical_price(type, T, K, sig, S + h, r, b);
			double term_2 = calculate_theoretical_price(type, T, K, sig, S - h, r, b);
			return (term_1 - term_2) / (2 * h);

		}

		// Approximates gamma greek
		double calculate_gamma_approximation(OptionType type, double T, double K, double sig, double S, double r, double b, double h)
		{
			double term_1 = calculate_theoretical_price(type, T, K, sig, S + h, r, b);
			double term_2 = calculate_theoretical_price(type, T, K, sig, S, r, b);
			double term_3 = calculate_theoretical_price(type, T, K, sig, S - h, r, b);
			return (term_1 - 2 * term_2 + term_3) / (h * h);
		}

		// Returns normal CDF value
		double N(double val)
		{
			normal_distribution<> nd;  // Default type is 'double'
			return cdf(nd, val);
		}

		// Returns normal PDF of value
		double n(double val)
		{
			normal_distribution<> nd;  // Default type is 'double'
			return pdf(nd, val);
		}

		// term used in european pricing
		double d1(double S, double K, double sig, double T, double b)
		{
			return (log(S / K) + (b + sig * sig * 0.5) * T) / (sig * sqrt(T)); // d1 = (ln(S/K) + (b+sig^2)*T/2)/(sig * sqrt(T))
		}

		// term used in european pricing
		double d2(double d1, double sig, double T)
		{
			return (d1 - sig * sqrt(T)); // d2 = d1 - sigma * sqrt(T)
		}

		bool have_same_option_values(Option& a, Option& b)
		{
			// Checks if two options have same exact parameters:
			// Specifically: Option Class, TTM, K, sig, S, r, b 
			//
			// We use epsilon comparison due to double precision issues
			// 0.001 is chosen to compare to nearest 10th of cent.
			double ERR = 0.001;
			if (a.option_class() != b.option_class()) { return false; } // If different Option classes, e.g: American vs European
			if (fabs(a.time_to_maturity() - b.time_to_maturity()) >= ERR) { return false; } // If time to maturity is not same
			if (fabs(a.strike_price() - b.strike_price()) >= ERR) { return false; } // If strike is not same
			if (fabs(a.volatility() - b.volatility()) >= ERR) { return false; } // If volatility is not same
			if (fabs(a.current_price() - b.current_price()) >= ERR) { return false; } // If current price is not same
			if (fabs(a.risk_free_rate() - b.risk_free_rate()) >= ERR) { return false; } // If risk free rate not same
			if (fabs(a.cost_of_carry() - b.cost_of_carry()) >= ERR) { return false; } // If cost of carry not same
			return true;
		}

		// Function that checks if two options are equal via put call parity
		bool check_put_call_parity(Option& a, Option& b)
		{
			double ERR = 0.001; // Precision error

			if (!have_same_option_values(a, b)) { return false; } // If the two options don't have same values, return false

			if (a.complement_option_type() != b.option_type()) { return false; } // Returns false if both options are same type, true if complements

			if (fabs(a.parity_price() - b.theoretical_price()) >= ERR) { return false; }

			return true; // if all statements pass, return true

		}
    }

}