#include "disease.hpp"

// constructor
Disease::Disease(double prob, int dur)
	: transmission_prob(prob), duration(dur), variant_id(current_variant) {};
// getter methods
double Disease::get_transmission_prob() const
{
	return transmission_prob;
}
int Disease::get_duration() const
{
	return duration;
}


int Disease::get_variant_id()
{
	return variant_id;
}	
int Disease::get_current_variant()
{
	return current_variant;
}
int Disease::get_transmissions()
{
	return transmissions;
}
int Disease::get_mutation_threshold()
{
	return mutation_threshold;
}


// method for mutations, called everytime get_infected() is called
void Disease::record_transmission()
{
	//increase the number of transmissions and mutate if the mutation threshold is reached.
	transmissions++;
	if (transmissions >= mutation_threshold) 
	{
        	mutate();
    	}
}

void Disease::mutate()
{
	//change the current variant which will affect all future Disease objects created
	current_variant++;
	// reset the number of transmissions
	transmissions = 0;

}


// setter method used in experiment 3
void Disease::set_mutation_threshold(int number)
{
	mutation_threshold = number;
}
