// Name: Koralp Takunyaci
// Seneca Student ID: 119716207
// Seneca email: ktakunyaci@myseneca.ca
// Date of completion: 03/12/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me

#include <iostream>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Workstation.h"
#include "Utilities.h"

namespace sdds
{
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		std::ifstream fstr(file);
		Utilities utils;
		std::string temp;


		if (!fstr) {
			throw std::string("ERROR! Cannot open the file");
		}

		

		while (getline(fstr, temp)) {
			size_t position = 0;
			bool more = true;
			std::string first, next;
			Workstation* firstStation;
			Workstation* nextStation;

			first = utils.extractToken(temp, position, more);
			firstStation = *std::find_if(stations.begin(), stations.end(), [&first](Workstation* station) {
				return station->getItemName() == first;
				});

			if (more) {
				next = utils.extractToken(temp, position, more);

				nextStation = *std::find_if(stations.begin(), stations.end(), [&next](Workstation* station) {
					return station->getItemName() == next;
					});

				if (nextStation) {
					firstStation->setNextStation(nextStation);
				}
			}
			activeLine.push_back(firstStation);
			
			
		}
		
		m_firstStation = activeLine.front();
		m_cntCustomerOrder = pending.size();
	}
	void LineManager::linkStations()
	{
		std::vector<Workstation*> sort;
		sort.push_back(m_firstStation);
		
		sort.push_back(m_firstStation->getNextStation());

		std::for_each(activeLine.begin(), activeLine.end() - 2, [&](Workstation* station)
			{
				sort.push_back(sort.back()->getNextStation());
			});
		activeLine = sort;
	}
	bool LineManager::run(std::ostream& os)
	{
		static size_t counter = 0;
		bool temp = false;

		os << "Line Manager Iteration: " << ++counter << std::endl;

		if (!pending.empty())
		{
			*activeLine.front() += std::move(pending.front());
			pending.pop_front();
		}

		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* station)
			{
				station->fill(os);
			});

		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* station)
			{
				station->attemptToMoveOrder();
			});

		if (m_cntCustomerOrder == (completed.size() + incomplete.size()))
		{
			temp = true;
		}
		return temp;
	}
	void LineManager::display(std::ostream& os) const
	{
		std::for_each(activeLine.begin(), activeLine.end(), [&os](Workstation* ws)
			{
				ws->display(os);
			});
	}
}