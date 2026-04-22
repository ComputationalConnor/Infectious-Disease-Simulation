#ifndef DISEASE_HPP      
#define DISEASE_HPP


class Disease
{
	private:
		// disease has a probability of transmission, and lasts for a number of days when infected
		double transmission_prob;
		int duration;
		int variant_id;

		// mutation, adding global variables for the variant and transmission counter
		static inline int current_variant = 0;
		static inline int transmissions = 0;
		static inline int mutation_threshold = 1000;
	public:
		Disease(double prob, int dur);
		double get_transmission_prob() const;
		int get_duration() const;
		
		int get_variant_id();
		static int get_current_variant();
		static int get_transmissions();
		static int get_mutation_threshold();
		static void set_mutation_threshold(int number);
		void record_transmission();
		static void mutate();






};


#endif
