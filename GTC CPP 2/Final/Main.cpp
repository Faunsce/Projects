#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <iomanip>
#include "Funcs.hpp"
#include "RandomNumber.tpp"
#include "Input.tpp"
#include "PoliceOfficer.hpp"
#include "ParkedCar.hpp"
#include "ParkingTicket.hpp"

int main() {
	try {
		bool goAgain = false;
		double city_revenue{ 0.0 };
		do {
			/// Data
			double max_time{ 180.0 };
			unsigned int parking_spaces{ 1u };
			unsigned int parking_freq{ 50u };
			unsigned int passTime{ 1u };

			/// Get officer name and create officer
			Custom::output("Please enter the name of the officer in the format of \"first last\"");
			PoliceOfficer officer(Custom::input<std::string>('\n'));

			/// Get parking space amount
			Custom::output("Please enter the number of parking spaces that exist within the street [Max 1k]");
			parking_spaces = Custom::input<unsigned int>(1u, 1000u);

			/// Get parking frequency
			Custom::output("Please enter the parking frequency [0-100] (not guaranteed)");
			parking_freq = Custom::input<unsigned int>(1u, 100u);

			/// Setup random cars
			std::vector<std::pair<ParkingMeter, std::shared_ptr<ParkedCar>>> streetSide;
			for (int i = 0; i < parking_spaces; i++) {
				if (Custom::randNum<unsigned int>(0u, 100u) < parking_freq) {
					std::shared_ptr<ParkedCar> tempCar = std::make_shared<ParkedCar>(
						static_cast<MAKE_MODEL>(Custom::randNum<unsigned int>(0u, static_cast<unsigned int>(MAKE_MODEL::DODGE_CHARGER))),
						static_cast<COLOR>(Custom::randNum<unsigned int>(0u, static_cast<unsigned int>(COLOR::BLACK)))
						);
					streetSide.emplace_back(std::make_pair(ParkingMeter(Custom::randNum<double>(0.0, 180.0)), tempCar));
				}
				else {
					streetSide.emplace_back(std::make_pair(ParkingMeter(Custom::randNum<double>(0.0, 180.0)), nullptr));
				}
			}

			/// Process the street and its cars 
			for (auto it = streetSide.begin(); it != streetSide.end(); it++) {
				if (it->second != nullptr) {
					it->second->passTime(Custom::randNum<float>(0.0, max_time * 2.0));
					Custom::output("Would you like to inspect parking space [" + std::to_string((int)(it - streetSide.begin())) + "] ( y / n )?");
					if (Custom::input<bool>()) // Check if the user wishes to examine the vehicle
						city_revenue += officer.examine(*it->second, it->first);
					Custom::output("All tickets on this car including the previous one");
					for (const auto& ticket : it->second->getTickets()) {
						std::cout << ticket << std::endl;
					}
				}
			}

			//
			Custom::output("Would you like to go again? ( y / n )");
			goAgain = Custom::input<bool>();
		} while (goAgain);

		// Calculate and present the value of all tickets issued to the player
		std::stringstream strm;
		strm << std::fixed << std::setprecision(2) << city_revenue;
		Custom::output("The Value of all tickets issued results in $" + strm.str() + " of city revenue");
	} catch (const std::exception& msg) {
		std::string message = msg.what();
		std::cout << std::endl << std::endl;
		for (int i = 0; i < message.length() / 9 ; i++) {
			std::cout << "[EXCEPTION] ";
		}
		std::cout << std::endl << std::endl;;
		std::cout << msg.what() << std::endl << std::endl;
		for (int i = 0; i < message.length() / 9; i++) {
			std::cout << "[EXCEPTION] ";
		}
	}

	std::cin.ignore(1);
}
