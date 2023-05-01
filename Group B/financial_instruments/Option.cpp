/*
* Option.cpp
* Defines the Option class methods
*/


// Standard Libraries
#include <cmath>
#include <stdlib.h>
#include <string>
#include <iostream>

#include <map>
#include <vector>

// Custom header
#include "Option.hpp"
#include "OptionConstants.hpp"
#include "OptionParameter.hpp"
#include "OptionFormulas.hpp"

using namespace std;

namespace Colin {
	namespace FinancialInstruments {

		double Option::h = 0.001; // Initialize static variable


		// Constructor for Shape object, defaulting with random ID
		Option::Option() : m_id(rand()), type(OptionType::Call), S(0), K(0), T(0), r(0), sig(0), b(0){}

		Option::Option(OptionType t, double ap, double sp, double ttm, double rf, double vol, double cc) : m_id(rand()), type(t), S(ap), K(sp), T(ttm), r(rf), sig(vol), b(cc)
		{
			/*
			* Parameters:
			* t: type of option (call or put)
			* ap: asset price
			* sp: strike price
			* ttm: time to maturity
			* rf: risk free rate
			* vol: constant volatility
			* cc: cost of carry
			*/
		}

		Option::Option(OptionType t, double ap, double sp, double rf, double vol, double cc) : m_id(rand()), type(t), S(ap), K(sp), T(INFINITY), r(rf), sig(vol), b(cc)
		{
			/*
			* Parameters:
			* t: type of option (call or put)
			* ap: asset price
			* sp: strike price
			* ttm: INFINITY
			* rf: risk free rate
			* vol: constant volatility
			* cc: cost of carry
			*/
		}

		Option::Option(const Option& o) : m_id(o.m_id), type(o.type), S(o.S), K(o.K), T(o.T), r(o.r), sig(o.sig), b(o.b){}

		Option::~Option() {}

		Option& Option::operator = (const Option& source)
		{
			if (this == &source) // if current address is the same as source's address
			{
				return *this; // return current object (avoid assignment on itself)
			}

			m_id = source.m_id; // assign current object's x value to be source's x value
			type = source.type;
			S = source.S;
			K = source.K;
			T = source.T;
			r = source.r;
			sig = source.sig;
			b = source.b;

			return *this; // return current object's pointer
		}

		void Option::set_parameter(OptionParameterType opt, double value)
		{
			switch (opt)
			{
			case StrikePrice: // If parameter was strike price
			{
				K = value;
				break;
			}
			case AssetPrice: // If parameter is current asset price
			{
				S = value;
				break;
			}
			case Maturity: // If parameter is maturity date
			{
				T = value;
				break;
			}
			case RFRate: // If parameter is risk free rate
			{
				r = value;
				break;
			}
			case Volatility: // If parameter is volatility
			{
				sig = value;
				break;
			}
			case CostOfCarry: // If parameter was cost of carry
			{
				b = value;
				break;
			}
			default: // Invalid case
			{
				cout << "Invalid Option Parameter" << endl;
				break;
			}
			}
		}

		void Option::set_h(double val) {
			h = val;
		}


		// Getter Methods to return private variables of option
		double Option::get(OptionParameterType opt) const
		{
			switch (opt)
			{
			case StrikePrice: // If parameter was strike price
			{
				return K;
			}
			case AssetPrice: // If parameter is current asset price
			{
				return S;
			}
			case Maturity: // If parameter is maturity date
			{
				return T;
			}
			case RFRate: // If parameter is risk free rate
			{
				return r;
			}
			case Volatility: // If parameter is volatility
			{
				return sig;
			}
			case CostOfCarry: // If parameter was cost of carry
			{
				return b;
			}
			default: // Invalid case
			{
				cout << "Invalid Option Parameter" << endl;
				return 0.0;
			}
			}
		}

		double Option::calculate(OptionFunctionType oft) const
		{
			switch (oft)
			{
			case TheoreticalPrice: // If user chooses Theoretical Price to calculate
			{
				return this->theoretical_price();
			}
			case Delta: // If user chooses Delta  to calculate
			{
				return this->delta();
			}
			case Gamma: // If user chooses Gamma  to calculate
			{
				return this->gamma();
			}
			case Vega: // If user chooses Vega to calculate
			{
				return this->vega();
			}
			case Theta: // If user chooses Theta to calculate
			{
				return this->theta();
			}
			case ApproxDelta: // If user chooses to Approximate Delta
			{
				return this->approximate_delta();
			}
			case ApproxGamma: // If user chooses to Approximate Gamma
			{
				return this->approximate_gamma();
			}
			default: // Invalid case
			{
				cout << "Invalid Option Function" << endl;
				return 0.0;
			}
			}

		}

		int Option::id() const { return m_id; }
		double Option::time_to_maturity() const { return T; }
		double Option::strike_price() const { return K; }
		double Option::volatility() const { return sig; }
		double Option::current_price() const { return S; }
		double Option::risk_free_rate() const { return r; }
		double Option::cost_of_carry() const { return b; }
		OptionType Option::option_type() const { return type; }
		OptionType Option::complement_option_type() const
		{
			// Returns the opposite of the current Option Type
			if (type == Call)
			{
				return Put;
			}
			return Call;
		}
		double Option::get_h() { return h; }
		
		double Option::delta() const
		{
			return calculate_delta(type, T, K, sig, S, r, b);
		}

		double Option::gamma() const
		{
			return calculate_gamma(type, T, K, sig, S, r, b);
		}

		double Option::vega() const
		{
			return calculate_vega(type, T, K, sig, S, r, b);
		}

		double Option::theta() const
		{
			return calculate_theta(type, T, K, sig, S, r, b);
		}

		double Option::approximate_delta() const
		{
			return calculate_delta_approximation(type, T, K, sig, S, r, b, h);
		}
		double Option::approximate_gamma() const
		{
			return calculate_gamma_approximation(type, T, K, sig, S, r, b, h);
		}


		double Option::parity_price() const
		{
			/*
			* Put-Call Parity: C + K*e^(-rT) = P + S
			* Put = C + K*e^(-rT) - S
			* Call = P + S - K*e^(-rT)
			*/
			if (type == OptionType::Call) // If option type is call
			{
				return this->theoretical_price() + K * exp(-r * T) - S;  // Return the theoretical put price
			}
			else if (type == OptionType::Put) // If option type is put
			{
				return this->theoretical_price() + S - K * exp(-r * T); // Return the theoretical call price
			}

			return 0.0;
		}
	}
}