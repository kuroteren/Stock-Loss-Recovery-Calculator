/*
Loss Recovery Calculator for Options Trading
by: Alexander Hess
::06072019
*/

#include <iostream>
#include <list>

using namespace std;

list<pair<int, float>> calculateRecovery(float cost, float loss, float price, int maxOptions);

int main()
{
	//variables
	float callCost, loss, callPrice, totalExpense;
	int shares, options, maxOptions;
	list<pair<int, float>> minCounts;
	bool showMath;
	char temp;

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

	cout << "Enter the max number of options you are willing to buy: ";
	cin >> maxOptions;

	cout << "Would you like the profit math shown at the end? (Y/N): ";
	cin >> temp;

	if (toupper(temp) == 'Y')
	{
		showMath = true;
	}
	else
	{
		showMath = false;
	}

	//Spacer
	cout << endl << endl << endl;

	totalExpense = callCost + callPrice;

	//Calculate Options count and price values
	minCounts = calculateRecovery(callCost, loss, callPrice, maxOptions);

	//On the off chance that no results are returned
	if (minCounts.size() == 0)
	{
		cout << "Unfortunately no amount of options can reasonably cover your losses." << endl;
	}
	else
	{
		//Iterate for output
		for (auto& itr : minCounts)
		{
			cout << "For " << itr.first << " options, minimum sale price to recover losses is: $";
			printf("%.2f", itr.second);
			cout << "\n\t This gives a total profit gain of $";
			printf("%.2f", ((itr.first * 100.00 * itr.second) - ((itr.first * 100.00 * totalExpense) + loss)));

			if (showMath)
			{
				cout << "\n\t Options sale value: ";
				cout << itr.first << " options * 100 shares * $" << itr.second << " = $";
				printf("%.2f", (itr.first * 100.00 * itr.second));
				cout << "\n\t Total loss and option expenses: ";
				cout << itr.first << " options * 100 shares * " << totalExpense << " + " << loss << "= $";
				printf("%.2f", ((itr.first * 100.00 * totalExpense) + loss));
			}

			cout << endl << endl;
		}
	}
}


list<pair<int, float>> calculateRecovery(float cost, float loss, float price, int maxOptions)
{
	list<pair<int, float>> values{};
	//Ease of use total cost variable
	float costPriceTotal = cost + price;

	//Options # loop
	/*
	loop set to break at 25 options, arbitrarily
		*will change in future to allow user set limit
	*/
	for (int i = 1; i <= maxOptions; i++)
	{
		//Minimum price loop
		/*
		j = costPriceTotal plus one cent as starting point
		this is due to any price less will not cover cost of options

		break value is costPriceTotal plus loss divided by 80
		*/
		for (float j = costPriceTotal + 0.01; j <= ((costPriceTotal + loss) / 80); j += 0.01)
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
->Multi-thread!!!!
->Expand calculator to take stock purchases outside of Options
->Add specific option count calculator, get minimum sell price for a specific number of options
*/

//So many comments!!!!
//Seriously think I commented this more than wrote code. -.-