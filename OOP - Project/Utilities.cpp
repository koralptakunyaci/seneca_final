// Name: Koralp Takunyaci
// Seneca Student ID: 119716207
// Seneca email: ktakunyaci@myseneca.ca
// Date of completion: 03/12/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me

#include <string>
#include "Utilities.h"

namespace sdds
{
	char Utilities::m_delimiter = ' ';

	Utilities::Utilities()
	{
	}

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string temp{};
		size_t position = str.find(m_delimiter, next_pos);

		if (position == next_pos)
		{
			more = false;
			throw "ERROR!";
		}
		if (position == std::string::npos)
		{
			more = false;
			temp = str.substr(next_pos);
		}
		else if (position != std::string::npos)
		{
			more = true;

			temp = str.substr(next_pos, position - next_pos);

			next_pos = position + 1;
			
		}

		if (temp.size() > m_widthField)
		{
			setFieldWidth(temp.size());
		}

		return temp;

	}
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
	
}