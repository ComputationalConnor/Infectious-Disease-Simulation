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
	
	cout << "Population: 10k, Transmission Probability: .3, Duration: 7 days, Contacts: 5" << endl;
	// iterate through every vaccination rate starting from .05 and keep going up, ideally would end whenever the disease lasts forever
	for(int i = 5; i<=100; i+=5)
	{

		cout << "Vaccination Rate " << i << endl;
		// keep track of the mutation threshold
		int mutation = 0;
		// start at a mutation threshold of 10,000 and keep going down until the disease lasts forever or reaches 0
		for(int j = 10000; j>=0; j-=50 )
		{
			Disease::set_mutation_threshold(j);
			Population UT(100);
			Disease flu(.3, 7);
			double rate = i/100.0;
       			UT.random_vaccination(rate);	
			UT.random_infection(flu);
	
			int time = 0; 
			// run the simulation until it either ends or lasts forever (more than 500 days)
			while(UT.num_sick()>0 && time<=500)
			{
				UT.contagion(true);
                		UT.spreading(5, true);
                		UT.one_more_day();
				time ++;
			}

			// check if the mutation lasted forever, if so, we found the threshold at which the disease survives forever
			if(time>500)
			{
				mutation = j;
				break;
				
			}
		}
		//print it out for recording
		cout << "mutation threshold where the disease wins " << mutation << endl;
	}
}
