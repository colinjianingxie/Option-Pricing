/*
* OptionConstants.hpp
* Provides template methods for all of Option Constants
*/
#ifndef OPTION_CONSTANTS_HPP // Verify we have unique HPP file reference
#define OPTION_CONSTANTS_HPP // Name the file OPTION_CONSTANTS_HPP

#include <string>
#include <iostream>

using namespace std;

namespace Colin {
	namespace FinancialInstruments {
        enum OptionType
        {
            Call = 'C',
            Put = 'P',
        };

        enum OptionParameterType {
            StrikePrice,
            AssetPrice,
            Maturity,
            RFRate,
            Volatility,
            CostOfCarry,
        };

        enum OptionFunctionType {
            TheoreticalPrice,
            Delta,
            Gamma,
            Vega,
            Theta,
            ApproxDelta,
            ApproxGamma,
        };

        enum OptionClass {
            European,
            American,
        };
	}
}
#endif // !OPTION_CONSTANTS_HPP
