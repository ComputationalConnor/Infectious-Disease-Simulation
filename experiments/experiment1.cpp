#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "disease.hpp"
#include "person.hpp"
#include "generate.hpp"
#include "population.hpp"
#include <format>
using std::format;

#include <thread>
#include <chrono>




int main()
{
	
	cout << "Population: 10k, Transmission Probability: .1, Duration: 7 days, Contacts: 5" << endl;

	// iterate through every vaccination from 0 to 100 with a 5% jump each time
	for(int i = 0; i<=100; i+=5)
	{

		cout << "Vaccination Rate " << i << endl;
		// establish average variable for the 100 runs
		double average = 0.0;
		// run the simulation 100 times and get the average duartion to account for randomness
		for(int j = 0; j<100; j++ )
		{
			// 100 * 100 = 10,000
			Population UT(100);
			Disease flu(.1, 7);
			double rate = i/100.0;
       			UT.random_vaccination(rate);	
			UT.random_infection(flu);
	
			int time = 0; 
			// basically keep running the simulation until there isn't anymore people infected
			while(UT.num_sick()>0)
			{
				// spread to neighbors
				UT.contagion(false);
				// contact 5 random people
                		UT.spreading(5, false);
				// progress through one day
                		UT.one_more_day();
				// keep track of the days passed
				time ++;
			}
			average += time;
		}
		average = average/100.0;
		cout << "Duration of the disease " << average << " days" << endl;
	}
}
