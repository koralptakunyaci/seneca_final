// Name: Koralp Takunyaci
// Seneca Student ID: 119716207
// Seneca email: ktakunyaci@myseneca.ca
// Date of completion: 03/12/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>

namespace sdds
{
	class Station
	{
		int id;
		std::string itemName;
		std::string description;
		size_t serialNum;
		size_t numItems;
		static size_t m_widthField;
		static size_t m_idGenerator;
	public:
		Station();
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif // !SDDS_STATION_H

