#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>


// Helper function for decimalToBase (do not call directly)
void printDecimalEq(int& prevQuotient, int& base, std::string& answer)
{
	std::cout << base << "|" <<prevQuotient << "  ";

	int remainder = prevQuotient % base;
	std::string remainderStr = std::to_string(remainder);

	// Used for handling the characters of remainders above 9
	if (remainder >= 10) {
		remainderStr = remainder - 10 + 'A';
	}
	answer += remainderStr;

	prevQuotient = std::floor(prevQuotient / base);
	std::cout << remainderStr;
	std::cout << std::endl;
}

void decimalToBase(long double value, int base, int decimalPrecision = 8)
{
	// The following code is for the integer part of the value
	int prevQuotient = std::floor(value);
	std::string answer = "";
	while (prevQuotient >= base)
	{
		printDecimalEq(prevQuotient, base, answer);
	}
	printDecimalEq(prevQuotient, base, answer);

	// Reverse to get the correct answer
	std::reverse(answer.begin(), answer.end());
	std::cout << "Answer Int: " <<  answer << std::endl;

	// The ff code is for the decimal part of the value
	long double decimal = value - std::floor(value);
	
	std::string ansDecimal = "";
	int currentLoop = 0; // To prevent infinite looping on irrational numbers

	while (decimal != 0 && currentLoop < 8)
	{
		long double newDecimal = decimal * base;
		char intAnswer;
		if (newDecimal >= 10)
			intAnswer = std::floor(newDecimal) + 'A' - 10;
		else
			intAnswer = std::floor(newDecimal) + '0';

		ansDecimal += intAnswer;
		std::cout << decimal << " * " << base << " = " << newDecimal << std::endl;
		decimal = newDecimal - std::floor(newDecimal);
		currentLoop++;
	}

	// Decimal part
	std::cout << "Answer Decimal: " << ansDecimal << std::endl;

	// Final answer
	std::cout << "=======================================" << std::endl;
	std::cout << answer << "." << ansDecimal << std::endl;
}

void baseToDecimal(long double value, int base, int decimalPrecision = 8)
{
	// For the integer part of value
	int intValue = std::floor(value);
	int intAns = 0;
	for (int digit = 0; digit < std::floor(std::log10(intValue)); digit++)
	{
		int digitValue = static_cast<int>(std::floor(intValue / std::pow(10, digit))) % 10;  // Returns the digit from intValue
		intAns += digitValue * static_cast<int>(std::pow(10, digit));
		std::cout << digitValue << " * " << "10^" << digit << digitValue * std::pow(10, digit);
	}
}

int main(int argc, char* argv[])
{
	for(int i = 1; i < argc; i++)
	{
		std::string command = argv[i];
		if (command == "--help")
		{
			std::cout << "-COMMANDS-\n" << 
			"--dec2Base [decimal] [base] -p [precision] " << 
			"| Converts a decimal to base, precision can be ommited (default 8)\n";
		}
		else if (command == "--dec2Base")
		{
			if (argv[i + 3] == "-p")
			{
				decimalToBase(std::stold(argv[i + 1]), std::stoi(argv[i + 2]), std::stoi(argv[i + 4]));	
				i+= 4;
			}
			else
			{
				decimalToBase(std::stold(argv[i + 1]), std::stoi(argv[i + 2]));	
				i+=2;
			}
			break;
		}
		else
		{
			std::cout << "Invalid Command: Type --help to view commands" << std::endl;
		}
	}
}
