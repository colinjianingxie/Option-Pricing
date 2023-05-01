/*
	Date: 4/19/2023
	Author: Colin Xie

	In this program, we will demonstrate exact solutions for Perpetual American Options
*/

// Standard Libraries
#include <iostream>
#include <vector>

// Custom headers
#include "financial_instruments/EuropeanOption.hpp"
#include "financial_instruments/AmericanPerpetualOption.hpp"
#include "financial_instruments/OptionConstants.hpp"
#include "financial_instruments/OptionParameter.hpp"
#include "financial_instruments/OptionManager.hpp"
#include "utils/Print.hpp"

// Boost libraries
#include <boost/range/irange.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>

using namespace std;
using namespace Colin::FinancialInstruments;
using namespace Colin::Utils;

// Global variables, used for testing - only to demonstrate for proof of concept

// Hardcoded batches for testing: Index 0 values are batch 1, index 1 values are batch 2, etc..
vector<double> T = { 0.25, 1.0, 1.0, 30.0 };
vector<double> K = { 65, 100, 10, 100.0 };
vector<double> sig = { 0.30, 0.2, 0.50, 0.30 };
vector<double> r = { 0.08, 0.0, 0.12, 0.08 };
vector<double> S = { 60, 100, 5, 100 };

// Generate various Option Parameters for testing, re-using values from batches in part a)
OptionParameter sampleMaturities(Maturity, T);
OptionParameter sampleVolatility(Volatility, sig);
OptionParameter sampleStrike(StrikePrice, K);
OptionParameter sampleRFRate(RFRate, r);
OptionParameter sampleAssetPrice(AssetPrice, S);
OptionParameter sampleCostOfCarry(CostOfCarry, r);

// Sample Parameter Grids
vector<OptionParameter> parameterGrid1 = { sampleMaturities, sampleVolatility, sampleStrike, sampleRFRate, sampleCostOfCarry, sampleAssetPrice }; // Pass in vector of parameters
vector<OptionParameter> parameterGrid2 = { sampleMaturities, sampleVolatility };

// Sample Options used for testing
EuropeanOption sampleCall = EuropeanOption(Call, S[0], K[0], T[0], r[0], sig[0], r[0]); // Create a european call from batch 1 parameters
EuropeanOption samplePut = EuropeanOption(Put, S[0], K[0], T[0], r[0], sig[0], r[0]); // Create a european put from batch 1 parameters

EuropeanOption greekCall = EuropeanOption(Call, 105, 100, 0.5, 0.1, 0.36, 0);
EuropeanOption greekPut = EuropeanOption(Put, 105, 100, 0.5, 0.1, 0.36, 0);

AmericanPerpetualOption americanCall = AmericanPerpetualOption(Call, 110, 100, 0.1, 0.1, 0.02); // Create a european call from batch 1 parameters
AmericanPerpetualOption americanPut = AmericanPerpetualOption(Put, 110, 100, 0.1, 0.1, 0.02); // Create a european call from batch 1 parameters


OptionManager manager; // Global options manager, utilized for 

vector<double> generate_range(int start, int end)
{
	vector<double> sampleRange; // defines range of price values
	boost::push_back(sampleRange, boost::irange(start, end+1)); // Use irange to cleanly generate range of values
	return sampleRange;
}

void test_pricing()
{
	/*
	* We iterate through each batch and calculate the respective Call/Put values
	* We will also check to see if put call parity is satisfied
	*/
	cout << "---Begin experiment for testing prices---" << endl;
	for (int i = 0; i < T.size(); i++) // Iterate through each batch, choosing arbitrary batch for size
	{
		// Note: we use b = r for Black Scholes
		EuropeanOption tempCall = EuropeanOption(Call, S[i], K[i], T[i], r[i], sig[i], r[i]);  // temporary call option for batch
		EuropeanOption tempPut = EuropeanOption(Put, S[i], K[i], T[i], r[i], sig[i], r[i]); // temporary put option for batch
		cout << "Batch " << i + 1 << " C = " << tempCall.theoretical_price() << ", P = " << tempPut.theoretical_price() << endl; // Print theo prices for both call and put
		cout << "Put Call Parity: C = " << tempPut.parity_price() << ", P = " << tempCall.parity_price() << endl; // Print parity prices for both call and put
		cout << "Put Call Parity Satisfied: " << check_put_call_parity(tempCall, tempPut) << endl; // Check if put call parity is satisified
	}
}

void test_parameter_range()
{
	OptionParameter sampleParameter(AssetPrice, generate_range(10, 50)); // create parameter vector with values [10...50]

	cout << "---Begin experiment for testing parameter range---" << endl;
	cout << "Options used for experiment:" << endl;
	cout << sampleCall << "--and--";
	cout << samplePut << "\n" << endl;

	// Method 1: Creating Option Parameter with custom vector of values
	cout << "\nMethod 1: Creating Option Parameter with custom vector of values" << endl;
	cout << "...adjusting price values from 10 to 50..." << endl;
	cout << "Call: ";
	print(manager.calculate_parameter(sampleCall, TheoreticalPrice, sampleParameter));
	cout << "Put: ";
	print(manager.calculate_parameter(samplePut, TheoreticalPrice, sampleParameter));

	// Method 2: Creating Option Parameter via start/end/steps
	cout << "\nMethod 2: Creating Option Parameter via start/end/steps" << endl;
	OptionParameter sampleParameter2(AssetPrice, 10, 50, 40);
	cout << "Call: ";
	print(manager.calculate_parameter(sampleCall, TheoreticalPrice, sampleParameter2));
	cout << "Put: ";
	print(manager.calculate_parameter(samplePut, TheoreticalPrice, sampleParameter2));
}

void test_parameter_grid()
{
	cout << "---Begin experiment for testing parameter grid---" << endl;
		
	vector<vector<double>> testResults;

	cout << "Option used for experiment:" << endl;
	cout << sampleCall << endl;

	cout << "\nPrices from parameter grid 1: " << endl;
	testResults = manager.matrix_pricer(sampleCall, TheoreticalPrice, parameterGrid1);
	print(testResults);
	cout << "\nPrices from parameter grid 2: " << endl;
	testResults = manager.matrix_pricer(sampleCall, TheoreticalPrice, parameterGrid2);
	print(testResults);
}

void test_greeks()
{
	cout << "---Begin experiment for testing greek calculations---" << endl;
	cout << "Options used for experiment:" << endl;
	cout << greekCall << "-- and --";
	cout << greekPut << "\n" << endl;
	cout << "Call Delta: " << greekCall.delta() << endl;
	cout << "Put Delta: " << greekPut.delta() << endl;
}

void test_greeks_parameter()
{

	OptionParameter sampleCallParameter(AssetPrice, generate_range(10, 51)); // create parameter vector adjusting asset price with values [10...50]
	vector<double> deltas = manager.calculate_parameter(greekCall, Delta, sampleCallParameter); // calculate values for delta given parameters
	
	cout << "Options used for experiment:" << endl;
	cout << greekCall << endl;
	cout << "Deltas obtained from adjusting asset prices from 10 to 50:" << endl;
	print(deltas);
}

void test_greeks_matrix()
{

	cout << "---Begin experiment for testing greek matrix calculations---" << endl;
	cout << "Options used for experiment:" << endl;
	cout << greekCall << "--and--";
	cout << greekPut << "\n" << endl;

	cout << "\nGrid deltas using parameterGrid1: ";
	print(manager.matrix_pricer(greekCall, Delta, parameterGrid1));

	cout << "\nGrid gammas using parameterGrid1: ";
	print(manager.matrix_pricer(greekCall, Gamma, parameterGrid1));

	cout << "\nGrid deltas using parameterGrid2: ";
	print(manager.matrix_pricer(greekPut, Delta, parameterGrid2));

	cout << "\nGrid gammas using parameterGrid2: ";
	print(manager.matrix_pricer(greekPut, Gamma, parameterGrid2));

}

void test_greeks_approximation()
{
	cout << "---Begin experiment for testing greek approximations---" << endl;
	cout << "Options used for experiment:" << endl;
	cout << greekCall << "-- and --";
	cout << greekPut << "\n" << endl;
	
	vector<double> h_values{ 10, 1, 0.1, 0.01, 0.001 };
	for (int i = 0; i < h_values.size(); i++)
	{
		greekCall.set_h(h_values[i]); // Since static, should change for both call and put
		cout << "h value: " << h_values[i] << endl;
		cout << "Call Delta: " << greekCall.delta() << ", Call Approximate Delta: " << greekCall.approximate_delta() << endl;
		cout << "Put Delta: " << greekPut.delta() << ", Put Approximte Delta: " << greekPut.approximate_delta() << endl;
		cout << "Call Gamma: " << greekCall.gamma() << ", Call Approximate Gamma: " << greekCall.approximate_gamma() << endl;
		cout << "Put Gamma: " << greekPut.gamma() << ", Put Approximte Gamma: " << greekPut.approximate_gamma() << endl;
		cout << "----" << endl;
	}
}

void test_perpetual_american_option()
{
	cout << "---Begin experiment for testing American Perpetual Options Pricing---" << endl;
	cout << "Options used for experiment:" << endl;
	cout << americanCall << "-- and --";
	cout << americanPut << "\n" << endl;
	cout << "American call price: " << americanCall.theoretical_price() << endl;
	cout << "American put price: " << americanPut.theoretical_price() << endl;
}

void test_perpetual_american_parameter()
{
	cout << "---Begin experiment for testing American Perpetual Options Pricing via parameters---" << endl;
	cout << "Options used for experiment:" << endl;
	cout << americanCall << "-- and --";
	cout << americanPut << "\n" << endl;
	OptionParameter sampleRange(AssetPrice, generate_range(10, 50)); // create parameter vector with values [10...50]
	cout << "American call prices: ";
	print(manager.calculate_parameter(americanCall, TheoreticalPrice, sampleRange));
	cout << "\nAmerican put prices: ";
	print(manager.calculate_parameter(americanPut, TheoreticalPrice, sampleRange));
}

void test_perpetual_american_grid()
{
	cout << "---Begin experiment for testing price grid on American Perpetual Options---" << endl;
	cout << "Options used for experiment:" << endl;
	cout << americanCall << endl;

	vector<OptionParameter> sampleParameterGrid = { sampleAssetPrice, sampleVolatility, sampleStrike };
	print(manager.matrix_pricer(americanCall, TheoreticalPrice, sampleParameterGrid));
}

int main()
{
	
	test_perpetual_american_option();
	cout << "<==========================================================>\n\n";
	test_perpetual_american_parameter();
	cout << "<==========================================================>\n\n";
	test_perpetual_american_grid();
}