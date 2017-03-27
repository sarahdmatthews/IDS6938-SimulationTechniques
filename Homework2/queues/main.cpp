/*
  A simple program that simulates 5 MM1 queues at an airport. The first queue
  feeds 3 other queues that work in parallel. These feed a final queue.
  Simulation runs until error below threshold and, at the end,
  a performance evaluation report is shown, and logs are generated
  for plotting and analysis.
*/

using namespace std;

#include <random>
#include "customer.h"
#include "mm1_queue.h"


std::random_device rd;

void pause()
{
 std::string sInputString;
 // Wait for input from stdin (the keyboard)
 cout << "Continue (y)?";
 std::cin >> sInputString;
}



int main(int argc, char* argv[])
{
   int next = 0;
//   test_random_number_generator();

   for (int cur_lambda = 3; cur_lambda < 34; cur_lambda++)
   {
      
	   //TODO Create MM1_Queue objects to capture the airport senario.

	   //************************************************************
	   //Information from Piazza MM1 Queue
	   MM1_Queue    IDCheckIn; //make 5 copies
	   IDCheckIn.set_file_names("IDCheckIn_log.txt", "IDCheckIn_wait.txt", "IDCheckIn_service.txt");
	   IDCheckIn.set_lambda(6);   // for this assignment this is set to a variable from the for loop.
	   IDCheckIn.set_mu(53);
	   IDCheckIn.autogenerate_new_arrivals(true); // to make sure there are no auto generated new arrivals add before initialize statement
	   IDCheckIn.initialize();
	   IDCheckIn.set_seed(1, rd()); // I set the first one to 1 for testing, the others you should use two random seeds (rd(), rd())

	   MM1_Queue    SecurityCheck; //make 5 copies
	   SecurityCheck.set_file_names("SecurityCheck.txt", "SecurityCheck.txt", "SecurityCheck.txt");
	   SecurityCheck.set_lambda(6);   // for this assignment this is set to a variable from the for loop.
	   SecurityCheck.set_mu(20);
	   SecurityCheck.autogenerate_new_arrivals(false); // to make sure there are no auto generated new arrivals add before initialize statement
	   SecurityCheck.initialize();
	   SecurityCheck.set_seed(1, rd()); // I set the first one to 1 for testing, the others you should use two random seeds (rd(), rd())
	   //do for security check 2 and 3 do for boardingplane

	   MM1_Queue    SecurityCheck2; //make 5 copies
	   SecurityCheck2.set_file_names("SecurityCheck2.txt", "SecurityCheck2.txt", "SecurityCheck2.txt");
	   SecurityCheck2.set_lambda(6);   // for this assignment this is set to a variable from the for loop.
	   SecurityCheck2.set_mu(20);
	   SecurityCheck2.autogenerate_new_arrivals(false); // to make sure there are no auto generated new arrivals add before initialize statement
	   SecurityCheck2.initialize();
	   SecurityCheck2.set_seed(1, rd()); // I set the first one to 1 for testing, the others you should use two random seeds (rd(), rd())
										//do for security check 2 and 3 do for boardingplane

	   MM1_Queue    SecurityCheck3; //make 5 copies
	   SecurityCheck3.set_file_names("SecurityCheck3.txt", "SecurityCheck3.txt", "SecurityCheck3.txt");
	   SecurityCheck3.set_lambda(6);   // for this assignment this is set to a variable from the for loop.
	   SecurityCheck3.set_mu(20);
	   SecurityCheck3.autogenerate_new_arrivals(false); // to make sure there are no auto generated new arrivals add before initialize statement
	   SecurityCheck3.initialize();
	   SecurityCheck3.set_seed(1, rd()); // I set the first one to 1 for testing, the others you should use two random seeds (rd(), rd())
										 //do for security check 2 and 3 do for boardingplane

	   MM1_Queue    BoardingPlane; //make 5 copies
	   BoardingPlane.set_file_names("BoardingPlane.txt", "BoardingPlane.txt", "BoardingPlane.txt");
	   BoardingPlane.set_lambda(6);   // for this assignment this is set to a variable from the for loop.
	   BoardingPlane.set_mu(80);
	   BoardingPlane.initialize();
	   BoardingPlane.set_seed(1, rd()); // I set the first one to 1 for testing, the others you should use two random seeds (rd(), rd())
										 //do for security check 2 and 3 do for boardingplane

   for (; 
		//TODO: add is_within_error_range check
	   													 //these are also checks
	   !IDCheckIn.is_within_error_range(0.002) ||
	   !SecurityCheck.is_within_error_range(0.002) ||
	   !SecurityCheck2.is_within_error_range(0.002) ||
	   !SecurityCheck3.is_within_error_range(0.002) ||
	   !BoardingPlane.is_within_error_range(0.002)

	   
       ;)
   {
	   Customer cust = IDCheckIn.process_next_event();    // =  TODO: process next event;
	   Customer cust2 = SecurityCheck.process_next_event();   // =  TODO: process next event;
	   Customer cust3 = SecurityCheck2.process_next_event();   // =  TODO: process next event;
	   Customer cust4 = SecurityCheck3.process_next_event();   // =  TODO: process next event;
	   Customer cust5 = BoardingPlane.process_next_event();   // =  TODO: process next event;
	   //TODO: one more process_next_event for the last object.

       if (cust.get_type() == Customer::COMPLETED())
       {
          switch(next)
          {
            case 0:
				//TODO add_external_arrival() for your security gates;
				SecurityCheck.add_external_arrival();
                 break;
            case 1:
				//TODO add_external_arrival() for your security gates;
				SecurityCheck2.add_external_arrival();
                 break;
            case 2:
                //TODO add_external_arrival() for your security gates;
				SecurityCheck3.add_external_arrival();
                 break;
          }
          next++;
          if (next%3==0) next = 0;
       }
       if (cust2.get_type() == Customer::COMPLETED() || cust3.get_type() == Customer::COMPLETED() || cust4.get_type() == Customer::COMPLETED())
       {
		   //TODO add_external_arrival(); on your final boarding MM1_Queue object
		   BoardingPlane.add_external_arrival();
		   

       }
   }



   //TODO Output statistics airport senario.
   //printing the outputs
   IDCheckIn.get_current_time();
	   IDCheckIn.plot_results_output();

   IDCheckIn.output(); cout << "*********" << endl;
   SecurityCheck.output(); cout << "*********" << endl;
   SecurityCheck2.output(); cout << "*********" << endl;
   SecurityCheck3.output(); cout << "*********" << endl;
   BoardingPlane.output(); cout << "*********" << endl;
   


   //**************************************************************************



   }

   return(0);
}




	
