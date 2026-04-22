#ifndef PERSON_HPP
#define PERSON_HPP

#include "disease.hpp"
// add optional class template so that a value can be null (in this case disease in the beginning)
#include <optional>
using std::optional;
using std::nullopt;

#include <vector>
using std::vector;


// create my own data type for the state of a person for clarity and convenience
enum class health_state
{
	SUSCEPTIBLE, SICK, RECOVERED, VACCINATED
};


class Person
{
	private:
		// a person has a status, the amount of days they've been sick, and their disease (if infected)
		health_state status;
		int days_sick;
		optional<Disease> disease;
		
		vector<int> variants_recovered;
	public:
		Person();
		void get_infected( Disease& new_disease);
		void get_vaccinated();
		void one_more_day();
		bool is_susceptible();
		bool is_infected();
		bool is_recovered();
		bool is_vaccinated();
		void contact( Disease& new_disease);
		void contact( Person& new_person);
		void contact_mutation( Person& new_person);


	









};

#endif
