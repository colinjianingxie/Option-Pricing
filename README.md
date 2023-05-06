
# Exact Pricing Methods

## Directory layout for each project

    .
    ├── financial_instruments                 # Source files for computing Options
    |   └── OptionConstants.hpp               # Holds all of the Option Constants
    |   └── Option.(hpp/cpp)	 				        # Abstract Base class of all Options
    |   └── EuropeanOption.(hpp/cpp)          # European Option
    |   └── AmericanPerpetualOption.(hpp/cpp) # American Option
    |   └── OptionManager.(hpp/cpp)           # Manager for Option functionalities
    |   └── OptionFormulas.(hpp/cpp)          # Formulas for calculating theoretical values
    ├── utils                                 # Utility files for general helpers
    |   └── Print.(hpp/cpp)                   # Print helper
    ├── main.cpp                              # Main driver program for each project
    └── README.md


## Usage
### Option Variables
```
int m_id; // id for each option
double T; // Time to maturity
double K; // Strike price
double sig; // volatility
double S; // current stock price
double r; // risk free rate
double b; // cost of carry parameter
static double h; // default gap for approximating greeks

// Option Enum Constants
OptionType type; // either (Call/Put)

// What function we want to calculate (TheoreticalPrice, Delta, Gamma, Vega...)
OptionFunctionType oft;

// Type of varying parameter being passed in to Option
// (StrikePrice, AssetPrice, Volatility, etc...)
OptionParameterType opt;

OptionClass oc; // Class of Option (European/American)


```
### Options
Currently, there are two supported Option classes: European and Perpetual American. To use them, you must import via:
 ```#include "financial_instruments/EuropeanOption.hpp"```
  ```#include "financial_instruments/AmericanPerpetualOption.hpp"```

They can be initialized via a default constructor or with parameters passed in. The constructor takes in parameters in the following order:
<b>European</b>: ```Option(type, S, K, T, r, sig, b)```
<b>American Perpetual</b>: ```Option(type, S, K, r, sig, b)```

For example:

```EuropeanOption sampleCall = EuropeanOption(Call, 105, 100, 0.5, 0.1, 0.36, 0)```

will generate a European Call with **current price** = 105, **strike price** = 100, etc..

### Option Parameter
When experimenting with a range of parameters, we must create an **OptionParameter** object.

To use **OptionParameter**, import via: ```#include "financial_instruments/OptionParameter.hpp" ```

The two most common ways to create an **OptionParameter**:
* Creating with custom vector of values:
	*  ```OptionParameter(OptionParameterType t, vector<double> values)```
* Creating with a range of values:
	* ```OptionParameter(OptionParameterType t, double start, double end, double mesh_size)```

For example:
```
vector<double> values = {10, 20, 30};
OptionParameter sampleParameter(StrikePrice, values);
```
will create a list of values to vary for the strike price of an option (K = 10, K=20, K=30).

To automatically create a range of values, we will need to generate the **OptionParamater** via the range constructor:
```
OptionParameter sampleParameter(AssetPrice, 10, 50, 40);
```
The above will generate a range of varying values for asset price, varying from (S=10, S=11, S=12, ... S=50), since the number of steps passed in is 40, the start value is 10, the end value is 50.

To expand on this idea, we can also create parameter grids or more specifically, a vector of **OptionParameter**. For example:

```vector<OptionParameter> parameterGrid = {sampleParameter1, sampleParameter2, ...} ```

### Option Manager
The **OptionManager** class allows the user to perform multiple analysis on options. To use the **OptionManager**, import via: ```#include "financial_instruments/OptionManager.hpp"``` and initialize: ```OptionManager manager;```

We can then perform multiple analysis:
```calculate_parameter(Option, OptionFunctionType, OptionParameter)```
Usage: Passes in vector of varying parameters, returns a vector of calculated values
For example:
 ```
vector<double> values = {10, 20, 30};
OptionParameter sampleParameter(StrikePrice, values);
vector<double> results = manager.calculate_parameter(sampleCall, Delta, sampleParameter);
 ```
 *results* would return a vector of calculated *delta* values of the *sampleCall* when the *strikePrice* is varied from values: 10, 20, 30.

```matrix_pricer(Option, OptionFunctionType, vector<OptionParameter>)```
Usage: Passes in matrix of varying parameters, returns a matrix of calculated values
Likewise, we can pass in a vector of **OptionParameter** to obtain calculated values:
```
vector<OptionParameter> parameterGrid = {sampleParameter1, sampleParameter2, ...};
vector<vector<double>> results = manager.matrix_pricer(sampleCall, TheoreticalPrice, parameterGrid );
```
This would return a matrix of calculated prices of the option *sampleCall* given a vector of varying parameters *parameterGrid*.

### Author
Jianing (Colin) Xie, developed 2023
