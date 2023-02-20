// Name: Koralp Takunyaci
// Seneca Student ID: 119716207
// Seneca email: ktakunyaci@myseneca.ca
// Date of completion: 03/12/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds
{
	extern std::deque<sdds::CustomerOrder> pending;
	extern std::deque<sdds::CustomerOrder> completed;
	extern std::deque<sdds::CustomerOrder> incomplete;

	class Workstation : public Station
	{
		std::deque<sdds::CustomerOrder> m_orders;
		Workstation* m_pNextStation;
	public:
		Workstation(const std::string& str);
		Workstation(const Workstation& cpy) = delete;
		Workstation& operator=(const Workstation& cpy) = delete;
		Workstation(Workstation&& move) noexcept = delete;
		Workstation& operator=(Workstation&& cpy) noexcept = delete;
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);

	};
}

#endif // !SDDS_WORKSTATION_H

