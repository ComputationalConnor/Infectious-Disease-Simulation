#include "disease.hpp"
#include "person.hpp"
#include "generate.hpp"
#include <vector>
#include <string>
#include <format>
#include <iostream>
using std::cout;
using std::endl;

using std::string;

class Population
{
 	private:
                // for making a 2D array, im using a single vector
                // a vector of a vector typically has poor performance
                vector<Person> people;
                int rows;
                int cols;
        public:
		Population(int size);
		Person& operator()(int i, int j);
		void random_infection(Disease& disease);
		void infect_edge(Disease& disease);
		void random_infection(Disease& disease, int count);
		void random_vaccination(double rate);
		void one_more_day();
		int num_susceptible();
		int num_vaccinated();
		int num_sick();
		int num_recovered();
		void display(string caption);
		void contagion(bool mutation);
		void spreading(int contact, bool mutation);
		


};
