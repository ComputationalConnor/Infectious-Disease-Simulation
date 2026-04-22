#include "person.hpp"
#include "generate.hpp"
#include <vector>
using std::vector;

#include <algorithm>

// Constructor, assume that a person isn't infected but can be.
Person::Person()
	: status(health_state::SUSCEPTIBLE), days_sick(0), disease(nullopt) {};

void Person::get_infected(Disease& new_disease)
{
		// when infected, status changes to SICK, person gets disease, and start the course
		status = health_state::SICK;
		// start: change from mutation
		// record a transmission and the person gets infected with a new disease object with the same parameters
		new_disease.record_transmission();
		disease = Disease(new_disease.get_transmission_prob(), new_disease.get_duration());
		// end: change from mutation
		days_sick = 0;
}

// change the health_status of the person to be VACCINATED
void Person::get_vaccinated()
{

	if(status == health_state::SUSCEPTIBLE)
	{
		status = health_state::VACCINATED;
	}

}

// progress the course of the disease one day if infected
void Person::one_more_day()
{
	if(status == health_state::SICK)
	{
		days_sick++;
		if(days_sick >= disease->get_duration())
		{
			status = health_state::RECOVERED;
			days_sick = 0;
			variants_recovered.push_back(disease->get_variant_id());
			disease = nullopt;
		
		}
	}

}
// check if the person is susceptible
bool Person::is_susceptible()
{
	if(status == health_state::SUSCEPTIBLE)
	{
		return true;
	}
	return false;
}
// check if the person is infected
bool Person::is_infected()
{
	if(status == health_state::SICK)
	{
		return true;
	}
	return false;
}
// check if the person is recovered
bool Person::is_recovered()
{
	if(status == health_state::RECOVERED)
	{
		return true;
	}
	return false;
}
//check if the person is vaccinated
bool Person::is_vaccinated()
{
	if(status == health_state::VACCINATED)
	{
		return true;
	}
	return false;
}
// create a contact interaction with a disease
void Person::contact( Disease& new_disease)
{	
	// in order to get a disease, must be susceptible status
	if(status == health_state::SUSCEPTIBLE)
	{
		//create a random number between 0 and 1
		double random = generator::random_double();
		//check if that random number is lower than the transmission probability
		if(random < new_disease.get_transmission_prob())
		{
			//if so then the person get's infected
			get_infected(new_disease);
		}
	}
	// if not nothing happens to the person

}

// create a contact interaction between two people
void Person::contact(Person& new_person)
{
	// for a person to give a disease to another, i need to be susceptible and the other sick
	if(status == health_state::SUSCEPTIBLE && new_person.is_infected())
	{
		Disease& dis = new_person.disease.value();
		// generate a random double between 0 and 1
		double random = generator::random_double();
		if(random < dis.get_transmission_prob())
		{
			get_infected(dis);
		}
	}
	

}


// method for contact but when the disease can mutate
void Person::contact_mutation(Person& new_person)
{
	// now recovered people and susceptible people can get infected still
	if((status == health_state::SUSCEPTIBLE || status == health_state::RECOVERED)&& new_person.is_infected())
	{
		Disease dis = new_person.disease.value();
		// checks if a person has been infected with the other person's variant before, if not then it will get infected
		if(status == health_state::SUSCEPTIBLE || std::count(variants_recovered.begin(),variants_recovered.end(), dis.get_variant_id()) == 0)
		{
			// generate a random double between 0 and 1
			double random = generator::random_double();
                	if(random < dis.get_transmission_prob())
                	{
				
                        	get_infected(dis);

                	}



		}


	}

}
