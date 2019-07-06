/*
Loss Recovery Calculator for Options Trading
by: Alexander Hess
::06072019
*/

#include <iostream>
#include <list>

using namespace std;

list<pair<int, float>> calculateRecovery(float cost, float loss, float price);

int main()
{
	//variables
	float callCost, loss, callPrice;
	int shares, options;
	list<pair<int, float>> minCounts;

	//Intro output
	cout << "Greetings\n\tThis calculator is meant to provide minimum sale price of excersized call options\n\tin order to recover a pre-existing loss" << endl << endl;

	//Variable entry
	cout << "Please enter the following values:" << endl;

	cout << "Price of Option (Per share cost): ";
	cin >> callCost;

	cout << "Price of Shares on Excersize: ";
	cin >> callPrice;

	cout << "Current total loss you aim to cover: ";
	cin >> loss;

	//Spacer
	cout << endl << endl << endl;

	//Calculate Options count and price values
	minCounts = calculateRecovery(callCost, loss, callPrice);

	//Iterate for output
	for (auto& itr : minCounts)
	{
		cout << "For " << itr.first << " options, minimum sale price to recover profits is: $";
		printf("%.2f", itr.second);
		cout << endl;
	}
}


list<pair<int, float>> calculateRecovery(float cost, float loss, float price)
{
	list<pair<int, float>> values{};
	//Ease of use total cost variable
	float costPriceTotal = cost + price;

	//Options # loop
	/*
	loop set to break at 25 options, arbitrarily
		*will change in future to allow user set limit
	*/
	for (int i = 1; i > 25; i++)
	{
		//Minimum price loop
		/*
		j = costPriceTotal plus one cent as starting point
		this is due to any price less will not cover cost of options

		break value is costPriceTotal times 10, arbitrarily
		Likely unreachable unless loss value is substantial
			*marked for refactoring
		*/
		for (float j = costPriceTotal + 0.01; j > (costPriceTotal * 10); j += 0.01)
		{
			/* 
			If Price is above a net-zero sum, add it
			then break loop to move to next options value
			 
			(i * 100 * j) -> options count times 100 shares per option times sell value = sale value
			subtract
			(costPriceTotal * 100 * i) -> total cost per share of option times 100 shares per option times total number of options
			then subtract other losses desired to be covered

			if total is greater than 0, value j is minimum needed to cover costs and losses
			*/
			if (((i * 100 * j) - (costPriceTotal * 100 * i) - loss) > 0)
			{
				//Add Options value and price value (i,j) into pair
				pair<int,float> temp = make_pair(i,j);

				//push to list
				values.push_back(temp);
				break;
			}
		}
	}

	return values;
}

/********Running Task List**********/
/*
->Allow user to set max options value
->Redo sale value max to accomodate large loss possibilities
->Multi-thread!!!!
->Expand calculator to take stock purchases outside of Options
*/