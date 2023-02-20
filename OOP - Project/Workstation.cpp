// Name: Koralp Takunyaci
// Seneca Student ID: 119716207
// Seneca email: ktakunyaci@myseneca.ca
// Date of completion: 03/12/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me

#include<iostream>
#include <iomanip>
#include "Workstation.h"

namespace sdds
{
	std::deque<sdds::CustomerOrder> pending{};
	std::deque<sdds::CustomerOrder> completed{};
	std::deque<sdds::CustomerOrder> incomplete{};

	Workstation::Workstation(const std::string& str) : Station(str) 
	{
		m_pNextStation = {};
	}

	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
		bool temp = false;

		if (!m_orders.empty())
		{
			if (m_orders.front().isItemFilled(getItemName()) && getQuantity() > 0)
			{
				if (!m_pNextStation)
				{
					if (!m_orders.front().isFilled())
					{
						incomplete.push_back(std::move(m_orders.front()));
					}
					else
					{
						completed.push_back(std::move(m_orders.front()));
					}
					
				}
				else
				{
					*m_pNextStation += std::move(m_orders.front());
				}
				m_orders.pop_front();
				temp = true;
			}
			else if (getQuantity() < 1)
			{
				if (!m_pNextStation)
				{
					if (!m_orders.front().isFilled())
					{
						incomplete.push_back(std::move(m_orders.front()));
					}
					else
					{
						completed.push_back(std::move(m_orders.front()));
					}

				}
				else
				{
					*m_pNextStation += std::move(m_orders.front());
				}
				m_orders.pop_front();
				temp = true;
			}
		}
		

		return temp;
	}

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const
	{
		os << Station::getItemName() << " --> ";
		if (m_pNextStation == nullptr)
		{
			os << "End of Line" << std::endl;
		}
		else
		{
			os << m_pNextStation->getItemName() << std::endl;
		}
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}

}