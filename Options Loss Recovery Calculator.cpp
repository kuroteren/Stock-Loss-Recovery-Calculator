// Options Loss Recovery Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>

using namespace std;

list<pair<int, float>> calculateRecovery(float cost, float loss, float price);

int main()
{
	float callCost, loss, callPrice;
	int shares, options;
	list<pair<int, float>> minCounts;

	cout << "Greetings\n\tThis calculator is meant to provide minimum sale price of excersized call options\n\tin order to recover a pre-existing loss" << endl << endl;

	cout << "Please enter the following values:" << endl;

	cout << "Price of Option (Per share cost): ";
	cin >> callCost;

	cout << "Price of Shares on Excersize: ";
	cin >> callPrice;

	cout << "Current total loss you aim to cover: ";
	cin >> loss;

	cout << endl << endl << endl;

	minCounts = calculateRecovery(callCost, loss, callPrice);

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
	float costPriceTotal = cost + price;

	for (int i = 1; ; i++)
	{
		for (float j = costPriceTotal + 0.01; ; j += 0.01)
		{
			if (((i * 100 * j) - (costPriceTotal * 100 * i) - loss) > 0)
			{
				pair<int,float> temp = make_pair(i,j);

				values.push_back(temp);
				break;
			}

			if (j > (costPriceTotal * 10))
			{
				break;
			}
		}

		if (i > 25)
		{
			break;
		}
	}

	return values;
}