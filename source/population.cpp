#include "disease.hpp"
#include "person.hpp"
#include "generate.hpp"
#include "population.hpp"
#include <vector>
#include <string>
#include <format>
using std::cout;
using std::endl;
#include <iostream>
using std::string;



using std::vector;


		// constructor
		Population::Population(int size)
			: rows(size), cols(size) {people.resize(size*size);};
		// () operator so that the information from the vector can be easily retrieved
		Person& Population::operator()(int i, int j)
		{
			return people[i*cols+j];
		}
		// randomly infects one person, used for patient zero
		void Population::random_infection(Disease& disease)
		{
			// generate a random number from 0 to 1 less than the total amount of people
			int random_person = generator::random_int(rows*cols);
			// infect the person at that index
			people[random_person].get_infected(disease);
		}

		void Population::infect_edge(Disease& disease)
		{
			people[0].get_infected(disease);
		}

		// randomly infects a specified number of people
		void Population::random_infection(Disease& disease, int count)
		{
			int size = rows*cols;
			// shuffle the indicies of the people in the vector
			vector<int> indices = generator::shuffle_people(size);
			
			// use the first "count" of people that get infected
			for(int i =0; i<count; i++)
			{
				// get the index
				int victim = indices[i];
				// person at that index gets infected
				people[victim].get_infected(disease);
			}

		}
		
		//vaccinates a number of people randomly based off the rate.
		void Population::random_vaccination(double rate)
		{
			int size = rows*cols;
			// get the number of people that need to be vaccinated to fufill the rate
			int to_vaccinate = (int)(size*rate);
			// shuffle the indicies of the people in the vector
			vector<int> indices = generator::shuffle_people(size);
			

			for(int i = 0; i<to_vaccinate; i++)
			{
				// get the random index
				int person_vax = indices[i];
				// person at that index gets infected
				people[person_vax].get_vaccinated();

			}	
		}
		
		// call the one_more_day method for every person in the vector
		void Population::one_more_day()
		{
			// iterate through every single person in the vector
			for(int i = 0; i<(rows*cols); i++)
			{
				people[i].one_more_day();

			}


		}
		
		// return the number of people that are susceptible in the population
		int Population::num_susceptible()
		{
			int count = 0;
			for(int i = 0; i<(rows*cols); i++)
			{
				if(people[i].is_susceptible())
				{
					count++;
				}
			}
			return count;
		}	
		
		//return the number of people that are vaccinated in the population
		int Population::num_vaccinated()
		{
			int count = 0;
                        for(int i = 0; i<(rows*cols); i++)
                        {
                                if(people[i].is_vaccinated())
                                {
                                        count++;
                                }
                        }
                        return count;
		}

		// return the number of people that are sick in the population
		int Population::num_sick()
		{
			int count = 0;
                        for(int i = 0; i<(rows*cols); i++)
                        {
                                if(people[i].is_infected())
                                {
                                        count++;
                                }
                        }
                        return count;
		}
		
		// return the number of people that are recovered in the population
		int Population::num_recovered()
		{
			int count = 0;
                        for(int i = 0; i<(rows*cols); i++)
                        {
                                if(people[i].is_recovered())
                                {
                                        count++;
                                }
                        }
                        return count;
		}
		
		// displays the population grid for visualization
		void Population::display(string caption = "") 
		{
			cout << std::format("\u{1b}[2J");
			cout << std::format("\u{1b}[0;0H");

			for(int i = 0; i<rows; i++)
			{
				for(int j = 0; j<cols; j++)
				{
					Person& person = people[i*cols+j];
				       	
					// '?' represents susceptible people
					char status = '?';
					string color_code = "\033[37m";
					
					// '+' represents infected people
					if(person.is_infected())
					{
						status = '+';
						color_code = "\033[31m";
					}

					// '-' represents people who can't get infected
					if(person.is_recovered() || person.is_vaccinated())
					{
						status = '-';
						color_code = "\033[32m";
					}

					cout << std::format("{}{}\033[0m ", color_code, status);

				}	
				
				cout << endl;
			}		

			cout << "======" << caption << "======" << endl;

		}

		// contacts a person with its neighbors
		void Population::contagion(bool mutation)
		{
			// depending on the bool, will either call the non-mutation or mutation contact method from the person class
			if(!mutation)
			{
			// create a new copy of people that will be updated throughout the method
			vector<Person> next_day = people;
			
			// iterate through everyone in the population
			for(int i = 0; i<rows; i++)
			{
				for(int j = 0; j<cols; j++)
				{
					// check if the people above, right, left, bottom are infected.
					// if so then call the contact method
					int index = i*cols+j;
					int above = (i-1)*cols+j;
					if(i-1>=0 && people[above].is_infected())
					{
						next_day[index].contact(people[above]);
					}
					int below = (i+1)*cols+j;
					if(i+1<rows && people[below].is_infected())
					{
						next_day[index].contact(people[below]);
					}
					int left = i*cols+(j-1);
					if(j-1>=0 && people[left].is_infected())
					{
						next_day[index].contact(people[left]);
					}
					int right = i*cols+(j+1);
					if(j+1<cols && people[right].is_infected())
					{
						next_day[index].contact(people[right]);
					}
				}

			}
			people = next_day;
			}
			// same code as above but just with the mutation contact method instead
			else
			{
			// create a new copy of people that will be updated throughout the method
                        vector<Person> next_day = people;

                        for(int i = 0; i<rows; i++)
                        {
                                for(int j = 0; j<cols; j++)
                                {
                                        int index = i*cols+j;
                                        int above = (i-1)*cols+j;
                                        if(i-1>=0 && people[above].is_infected())
                                        {
                                                next_day[index].contact_mutation(people[above]);
                                        }
                                        int below = (i+1)*cols+j;
                                        if(i+1<rows && people[below].is_infected())
                                        {
                                                next_day[index].contact_mutation(people[below]);
                                        }
                                        int left = i*cols+(j-1);
                                        if(j-1>=0 && people[left].is_infected())
                                        {
                                                next_day[index].contact_mutation(people[left]);
                                        }
                                        int right = i*cols+(j+1);
                                        if(j+1<cols && people[right].is_infected())
                                        {
                                                next_day[index].contact_mutation(people[right]);
                                        }
                                }

                        }
                        people = next_day;

			}


		}

		// this method infects a specified number of random people in the population
		// similar to an infected person traveling
		void Population::spreading(int contact, bool mutation)
		{
			if(!mutation)
			{
			vector<Person> next_day = people;
			int pop = people.size();
			// go through the entire population to check for infected people
			for(int i =0; i<pop; i++)
			{
				// if a person is infected, then they will contact a number of random people
				if(people[i].is_infected())
				{
					for(int j =0; j<contact; j++)
					{
						// generate a random integer that is between 0 and the population size -1
						// this number will be used to choose the random person that will be contacted
						int victim = generator::random_int(pop);
						// if doing mutation do contact_mutation
						next_day[victim].contact(people[i]);
					}
				}


			}

			people = next_day;
			}
			// similar to the code above but with the contact mutate method
			else
			{
			vector<Person> next_day = people;
                        int pop = people.size();

                        for(int i =0; i<pop; i++)
                        {
                                if(people[i].is_infected())
                                {
                                        for(int j =0; j<contact; j++)
                                        {
                                                int victim = generator::random_int(pop);
                                                // if doing mutation do contact_mutation
                                                next_day[victim].contact_mutation(people[i]);
                                        }
                                }


                        }

                        people = next_day;


			}
		}
