#ifndef GENERATE_HPP    
#define GENERATE_HPP

#include <random>
#include <numeric>
#include <algorithm>
#include <vector>

using std::vector;

// generator class to make static methods for random number generation and shuffling
class generator
{
	private:
		// establish the default random engine
		static inline std::default_random_engine engine{std::random_device{}()};
	public:
		// generate a random double between 0 and 1
		static double random_double()
		{
			std::uniform_real_distribution<double> dist(0.0,1.0);
			return dist(engine);
		};
		
		// generate a random integer from 0 to max-1
		static int random_int(int max)
		{
			std::uniform_int_distribution<int> dist(0,max-1);
			return dist(engine);
		};
		
		// used in the random_vaccination method, return shuffled indicies of people
		// the shuffled indicies will be used to determine who randomly gets vaccinated
		static vector<int> shuffle_people(int total)
		{
			//create a integer vector of the same size as the population
			vector<int> people_indices(total);
			
			// Fill the vector with its individual indices
			std::iota(people_indices.begin(), people_indices.end(), 0);

			std::shuffle(people_indices.begin(), people_indices.end(), engine);

			return people_indices;	
		}
};




#endif
