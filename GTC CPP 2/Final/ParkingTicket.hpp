#pragma once
#include "PoliceOfficer.hpp"
#include "ParkedCar.hpp"
#include "ParkingMeter.hpp"
#include <string>

class ParkedCar;
class PoliceOfficer;
class ParkingMeter;

class ParkingTicket 
{
public:
	// Constructors
	ParkingTicket() = default;
	ParkingTicket(const ParkedCar&, const PoliceOfficer&, const ParkingMeter&);
	// Output
	friend std::ostream& operator<<(std::ostream& strm, const ParkingTicket& obj);
	// Getters
	double getFine() const;
	std::string getMake() const;
	std::string getModel() const;
	std::string getColor() const;
	unsigned short getPlate() const;
	std::string getName() const;
	unsigned short getBadge() const;
private:
	std::string make;
	std::string model;
	std::string color;
	unsigned short plate;
	double fine;
	std::string issuing_officer;
	unsigned short officer_badge;
};
