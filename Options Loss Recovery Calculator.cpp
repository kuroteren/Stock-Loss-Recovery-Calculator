/*
Loss Recovery Calculator for Options Trading
by: Alexander Hess
::06072019
*/

#include <iostream>
#include <list>
#include <thread>
#include <vector>
#include <algorithm>

using namespace std;

static void calculateRecovery(float cost, float loss, float price, int options, list<pair<int, float>> *minCounts);

void join_thread(thread& t);

void join_all_threads(vector<thread>& v);

int main()
{
	//variables
	float callCost, loss, callPrice, totalExpense;
	int maxOptions;
	static list<pair<int, float>> * minCounts = new list<pair<int,float>>();
	bool showMath;
	char temp;
	vector<thread> threadVector;

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
	for (int i = 1; i <= maxOptions; i++)
	{
		threadVector.push_back(thread( calculateRecovery, callCost, loss, callPrice, i, ref(minCounts) ));
	}

	join_all_threads(threadVector);

	(*minCounts).sort();

	//On the off chance that no results are returned
	if ((*minCounts).size() == 0)
	{
		cout << "Unfortunately no amount of options can reasonably cover your losses." << endl;
	}
	else
	{
		//Iterate for output
		for (auto& itr : (*minCounts))
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

	system("pause");
}

static void calculateRecovery(float cost, float loss, float price, int options, list<pair<int, float>>* minCounts)
{
	//Ease of use total cost variable
	float costPriceTotal = cost + price;

	//Minimum price loop
	/*
	j = costPriceTotal plus one cent as starting point
	this is due to any price less will not cover cost of options

	break value is costPriceTotal plus loss divided by 80
	*/
	for (float j = costPriceTotal + 0.01; j <= (costPriceTotal + loss); j += 0.01)
	{
		/*
		If Price is above a net-zero sum, add it
		then break loop to move to next options value

		(options * 100 * j) -> options count times 100 shares per option times sell value = sale value
		subtract
		(costPriceTotal * 100 * options) -> total cost per share of option times 100 shares per option times total number of options
		then subtract other losses desired to be covered

		if total is greater than 0, value j is minimum needed to cover costs and losses
		*/
		if (((options * 100 * j) - (costPriceTotal * 100 * options) - loss) >= 0)
		{
			//Add Options value and price value (i,j) into pair
			pair<int, float> temp = make_pair(options, j);

			//push to list
			(*minCounts).push_back(temp);
			break;
		}
	}
}

void join_thread(thread& t)
{
	t.join();
}

void join_all_threads(vector<thread>& v)
{
	for_each(v.begin(), v.end(), join_thread);
}

/********Running Task List**********/
/*
->Expand calculator to take stock purchases outside of Options
->Add specific option count calculator, get minimum sell price for a specific number of options
*/

//So many comments!!!!
//Seriously think I commented this more than wrote code. -.-