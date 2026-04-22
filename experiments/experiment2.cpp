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

	cout << "Population: 10k, Duration: 7 days, Contacts: 5" << endl;
// iterate through transmission probabilties from .05 to 1.0 with a .05 jump
for(int k = 50; k<=1000; k+=50)
{
	 double transmission_prob = k/1000.0;
	 cout << "Transmission Probability " << transmission_prob << endl;
	// iterate from vaccination rates starting from 99.5 and progressively going down until "herd immunity" is reached
	for(int i =995; i>=0; i-=5)
	{
		// this average will be the average proportion of the non vaccinated people who dont get sick to total amount of non vaccinated people
    		double average = 0.0;
		// run the simulation 100 times
    		for(int j = 0; j<100; j++)
    		{
        		// 100 * 100 = 10,000
        		Population UT(100);
        		Disease flu(transmission_prob, 7);
        		double rate = i/1000.0;
        		UT.random_vaccination(rate);
        		UT.random_infection(flu);
			// keep track of the total number of non-vaccinated people
        		double initial_susceptible = (double)UT.num_susceptible();
			// run the simulation until the disease has taken its course
        		while(UT.num_sick()>0)
        		{
            			UT.contagion(false);
            			UT.spreading(5, false);
            			UT.one_more_day();
        		}
		//get the number of non-vaccinated people who never got sick
        	double final_susceptible = (double)UT.num_susceptible();
        	average += final_susceptible/initial_susceptible;
    	}

    	average = average/100.0;
	// I essentially want to get the lowest vaccination rate to where herd immunity is still acheived in my simulation
    	if(average<.95)
    	{
		cout << "Vaccination Rate " << i/1000.0 << endl;
		cout << average << " of non vaccinated people never got the disease" << endl;
        	break;

    	}

	}
}	
}
