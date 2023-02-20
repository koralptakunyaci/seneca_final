// Name: Koralp Takunyaci
// Seneca Student ID: 119716207
// Seneca email: ktakunyaci@myseneca.ca
// Date of completion: 03/12/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include "Station.h"

namespace sdds
{
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder
	{
		std::string m_name = {};
		std::string m_product = {};
		size_t m_cntItem = 0;
		Item** m_lstItem = nullptr;

		// Class Variable
		static size_t m_widthField;
	public:
		CustomerOrder();
		CustomerOrder(const std::string&);
		CustomerOrder(const CustomerOrder& obj);
		CustomerOrder& operator=(const CustomerOrder& obj) = delete;
		CustomerOrder(CustomerOrder&& obj) noexcept;
		CustomerOrder& operator=(CustomerOrder&& obj) noexcept;
		~CustomerOrder();
		bool isFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;


	};
}


#endif // !SDDS_CUSTOMERORDER_H

