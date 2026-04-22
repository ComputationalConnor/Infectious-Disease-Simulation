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

#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"



TEST_CASE("Person infection with 100% transmittable disease", "[person]") {
    Disease deadly_disease(1.0, 5); // 100% transmission, lasts 5 days
    Person person;

    SECTION("Susceptible person gets infected") {
        REQUIRE(person.is_susceptible());
        person.get_infected(deadly_disease);
        REQUIRE(person.is_infected());
        REQUIRE_FALSE(person.is_susceptible());
    }
}
TEST_CASE("Vaccinated and recovered persons don't get infected", "[person]") {
    Disease deadly_disease(1.0, 5);
    
    SECTION("Vaccinated person stays vaccinated") {
        Person person;
        person.get_vaccinated();
        REQUIRE(person.is_vaccinated());

	person.contact(deadly_disease);
        REQUIRE(person.is_vaccinated());
        REQUIRE_FALSE(person.is_infected());
	}

	SECTION("Recovered person stays recovered") {
        	Person person;
        
        	// First infect and recover
        	person.get_infected(deadly_disease);
        	REQUIRE(person.is_infected());
        
        	// Progress through sickness to recovery
        	for (int i = 0; i < deadly_disease.get_duration(); i++) {
            		person.one_more_day();
        	}
        	REQUIRE(person.is_recovered());
        
        
        	person.contact(deadly_disease);
        	REQUIRE(person.is_recovered());
        	REQUIRE_FALSE(person.is_infected());
    }

}



TEST_CASE("50% transmission probability infects about half", "[person]") {

	Disease half_chance_disease(0.5, 5);
	SECTION("Statistical test with random values") {
        const int num_people = 10000;
        int infections = 0;
        
        
        for (int i = 0; i < num_people; i++) {
            Person person;
            person.contact(half_chance_disease);  // Uses random generator
            if (person.is_infected()) {
                infections++;
            }
        }
       	cout << infections << endl; 
        double infection_rate = (double)infections / num_people;
        REQUIRE(infection_rate < 0.6);
	REQUIRE(infection_rate > 0.4);
    }
}




TEST_CASE("Person to person contact")
{
    
    Disease flu(1.0, 7);
    Person sick, healthy;
    
    // Debug sick person
    sick.get_infected(flu);
    healthy.contact(sick);
    REQUIRE(healthy.is_infected());
    

}


TEST_CASE("Population testing")
{
	// test that initial population is healthy
	Population pop(10);
	REQUIRE(pop.num_susceptible() == 100);
	
	pop.random_vaccination(1.0);
	// test that everyone gets vaccinated if the rate is 1.0
	REQUIRE(pop.num_susceptible() == 0);
	REQUIRE(pop.num_vaccinated() == 100);
	
	//test that when everyone is infected, everyone recovers eventually
	Population pop1(2);
	Disease flu(.5, 4);
	pop1.random_infection(flu, 4);
	REQUIRE(pop1.num_sick() == 4);
	REQUIRE(pop1.num_susceptible() == 0);
	pop1.one_more_day();
	pop1.one_more_day();
	pop1.one_more_day();
	pop1.one_more_day();
	pop1.one_more_day();
	REQUIRE(pop1.num_recovered() == 4);
	REQUIRE(pop1.num_sick() == 0);

/*
	cout << "Test to see if the number of infected people stay constant for disease duration" << endl;	
	Population pop2(2);
	Disease test1(0.0, 5);
	pop2.random_infection(test1, 4);
	for ( int day=0; day<6; day++ ) 
	{
		pop2.display( format( "Day: {}",day ) );
		std::this_thread::sleep_for( std::chrono::milliseconds(500) );
		pop2.one_more_day();
	}


	cout << "Check if the number of heatlhy and infected people equals the population size" << endl;
	Population pop3(2);
        Disease test2(0.0, 5);
        pop3.random_infection(test2, 2);
        for ( int day=0; day<6; day++ )
        {
                pop3.display( format( "Day: {}",day ) );
		std::this_thread::sleep_for( std::chrono::milliseconds(500) );
                pop3.one_more_day();
        }
*/

}

/*
TEST_CASE("Contagion Testing")
{
	cout << "49.3.2.1 Tests" << endl;
	Population contagion_case(4);
	Disease black_death(1.0, 5);
	contagion_case.infect_edge(black_death);
	for ( int day=0; day<10; day++ )
        {
                contagion_case.display( format( "Day: {}",day ) );
		std::this_thread::sleep_for( std::chrono::milliseconds(500) );
                contagion_case.contagion();
		contagion_case.one_more_day();
        }


	
        Population contagion2(4);
        Disease half(.5, 5);
        contagion2.infect_edge(half);
        for ( int day=0; day<10; day++ )
        {
                contagion2.display( format( "Day: {}",day ) );
		std::this_thread::sleep_for( std::chrono::milliseconds(500) );
                contagion2.contagion(false);
		contagion2.one_more_day();
        }

}
*/

/*
TEST_CASE("Vaccination Testing")
{
	cout << "Vaccination Testing" << endl;
	Population vaccinated(10);
	Disease measles(.5, 5);
	vaccinated.random_vaccination(.4);
	vaccinated.random_infection(measles);
	for ( int day=0; day<10; day++ )
        {
                vaccinated.display( format( "Day: {}",day ) );
		std::this_thread::sleep_for( std::chrono::milliseconds(500) );
                vaccinated.contagion(false);
		vaccinated.one_more_day();
        }
}

*/
/*
TEST_CASE("Spreading Testing")
{
	cout << "Testing with spreading" << endl;
	Population UT(50);
	Disease ligma(.2, 5);
	UT.random_infection(ligma);
	UT.random_vaccination(.8);
	for (int day = 0; day<30; day++)
	{
		UT.display(format( "Day: {}", day));
		std::this_thread::sleep_for( std::chrono::milliseconds(500) );
		UT.contagion(false);
		UT.spreading(6, false);
		UT.one_more_day();
	}
}
*/

TEST_CASE("Mutation Testing")
{

	cout << "Testing with mutations" << endl;
	Population TAMU(10);
	Disease son_syndrome(.5, 5);
	TAMU.random_infection(son_syndrome);
	TAMU.random_vaccination(.5);
	for (int day = 0; day<30; day++)
        {
                TAMU.display(format( "Day: {}", day));
                std::this_thread::sleep_for( std::chrono::milliseconds(500) );
                TAMU.contagion(true);
                TAMU.spreading(6, true);
                TAMU.one_more_day();
        }




}

