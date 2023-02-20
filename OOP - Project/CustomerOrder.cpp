// Name: Koralp Takunyaci
// Seneca Student ID: 119716207
// Seneca email: ktakunyaci@myseneca.ca
// Date of completion: 03/12/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me

#include <iostream>
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds
{
	size_t CustomerOrder::m_widthField = 0;


	CustomerOrder::CustomerOrder()
	{
		m_name = {};
		m_product = {};
		m_cntItem = 0;
		m_lstItem = nullptr;
	}

	CustomerOrder::CustomerOrder(const std::string& str) 
	{
		Utilities utils;
		size_t pos = 0;
		bool more = true;

		m_name = utils.extractToken(str, pos, more);
		m_product = utils.extractToken(str, pos, more);
		m_cntItem = 0;
		size_t tempPos = pos;
		
		while (more)
		{
			utils.extractToken(str, pos, more);
			m_cntItem++;
		}

		m_lstItem = new Item * [m_cntItem];

		for (size_t i = 0; i < m_cntItem; i++)
		{
			m_lstItem[i] = new Item(utils.extractToken(str, tempPos, more));
		}
		
		if (CustomerOrder::m_widthField < utils.getFieldWidth())
		{
			CustomerOrder::m_widthField = utils.getFieldWidth();
		}
	}
	

	CustomerOrder::CustomerOrder(const CustomerOrder& obj)
	{
		throw "ERROR: Cannot make copies.";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& obj) noexcept
	{
		if (this != &obj)
		{
			*this = std::move(obj);
		}
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& obj) noexcept
	{
		if (this != &obj)
		{
			if (m_lstItem)
			{
				for (size_t i = 0; i < m_cntItem; i++)
				{
					delete m_lstItem[i];
					m_lstItem[i] = nullptr;
				}
				delete[] m_lstItem;
				m_lstItem = nullptr;

			}

			m_name = obj.m_name;
			m_product = obj.m_product;
			m_cntItem = obj.m_cntItem;
			m_lstItem = obj.m_lstItem;


			obj.m_name = {};
			obj.m_product = {};
			obj.m_cntItem = 0;
			obj.m_lstItem = nullptr;

		}

		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			delete m_lstItem[i];
			m_lstItem[i] = nullptr;
		}
		delete[] m_lstItem;
		
	}

	bool CustomerOrder::isFilled() const
	{
		bool temp = true;

		for (size_t i = 0; i < m_cntItem && temp; i++)
		{
			if (m_lstItem[i]->m_isFilled)
			{
				temp = true;
			}
			else
			{
				temp = false;
			}
		}
		return temp;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool temp = true;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				if(m_lstItem[i]->m_isFilled)
					temp = true;
				else
				{
					temp = false;
				}
			}

		}
		return temp;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		std::for_each(m_lstItem, (m_lstItem + m_cntItem), [&](Item*& item)
			{
				if (item->m_itemName == station.getItemName())
				{
					if (station.getQuantity() > 0)
					{
						station.updateQuantity();
						item->m_serialNumber = station.getNextSerialNumber();
						item->m_isFilled = true;

						os << "    Filled " << m_name
							<< ", " << m_product
							<< " [" << item->m_itemName
							<< "]" << std::endl;
					}
					else
					{
						os << "    Unable to fill " << m_name
							<< ", " << m_product
							<< " [" << item->m_itemName
							<< "]" << std::endl;
					}
				}
			});
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;

		std::for_each(m_lstItem, (m_lstItem + m_cntItem), [&os](Item*& item)
			{
				os << "[" << std::setw(6) << std::right << std::setfill('0')
					<< item->m_serialNumber << "] "
					<< std::setw(m_widthField) << std::setfill(' ') << std::left << item->m_itemName << " - ";
				if (item->m_isFilled)
				{
					os << "FILLED" << std::endl;
				}
				else
				{
					os << "TO BE FILLED" << std::endl;
				}

			});

	}

}

