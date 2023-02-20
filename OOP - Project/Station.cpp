// Name: Koralp Takunyaci
// Seneca Student ID: 119716207
// Seneca email: ktakunyaci@myseneca.ca
// Date of completion: 03/12/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me

#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"



namespace sdds
{
	
	size_t Station::m_widthField = 0;
	size_t Station::m_idGenerator = 0;

	sdds::Station::Station()
	{
		id = 0;
		itemName = {};
		description = {};
		serialNum = 0;
		numItems = 0;
	}

	sdds::Station::Station(const std::string& str)
	{
		Utilities utils;
		size_t position = 0;
		bool more = true ;

		id = ++m_idGenerator;

		itemName = utils.extractToken(str, position, more);

		serialNum = std::stoi(utils.extractToken(str, position, more));

		numItems = std::stoi(utils.extractToken(str, position, more));

		description = utils.extractToken(str, position, more);

		if (itemName.size() > m_widthField)
			m_widthField = itemName.size();

	}

	const std::string& sdds::Station::getItemName() const
	{
		return itemName;
	}

	size_t sdds::Station::getNextSerialNumber()
	{
		return serialNum++;
	}

	size_t sdds::Station::getQuantity() const
	{
		return numItems;
	}

	void sdds::Station::updateQuantity()
	{
		if (numItems > 0)
		{
			--numItems;
		}
	}

	void sdds::Station::display(std::ostream& os, bool full) const
	{
		os << "[" << std::setw(3) << std::right <<std::setfill('0') << id << "] " << std::setfill(' ');
		os << "Item: " << std::left << std::setw(m_widthField) <<  itemName << std::right;
		os << " [" << std::setw(6) << std::setfill('0')  << serialNum << "]" << std::setfill(' ');

		if (full == true)
			os << " Quantity: " << std::left << std::setw(m_widthField) <<  numItems << std::right << " Description: " << description;

		os << std::endl;
	}

}



