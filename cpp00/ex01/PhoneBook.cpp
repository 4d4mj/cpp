#include "PhoneBook.hpp"
#include <iostream>
#include <limits>
#include <iomanip>
#include <cstdlib>

std::string getInput(const std::string &prompt)
{
	std::string input;
	while (true)
	{
		std::cout << prompt;
		std::getline(std::cin, input);
		if (input.empty())
		{
			std::cout << "Input cannot be empty. Please enter a value or type 'exit' to cancel: ";
			std::getline(std::cin, input);
			if (input == "exit")
				return "";
		}
		if (!input.empty())
			break;
	}
	return input;
}

PhoneBook::PhoneBook() : nextIndex(0) {}

void PhoneBook::addContact()
{
	Contact newContact;
	std::string input;

	input = getInput("Enter First Name: ");
	if (input.empty())
		return;
	newContact.setFirstName(input);

	input = getInput("Enter Last Name: ");
	if (input.empty())
		return;
	newContact.setLastName(input);

	input = getInput("Enter Nickname: ");
	if (input.empty())
		return;
	newContact.setNickname(input);

	input = getInput("Enter Phone Number: ");
	if (input.empty())
		return;
	newContact.setPhoneNumber(input);

	input = getInput("Enter Darkest Secret: ");
	if (input.empty())
		return;
	newContact.setDarkestSecret(input);

	contacts[nextIndex] = newContact;
	nextIndex = (nextIndex + 1) % 8;
	std::cout << "Contact added successfully." << std::endl;
}

void PhoneBook::searchContacts() const
{
	std::cout << std::setw(10) << "Index" << "|";
	std::cout << std::setw(10) << "First Name" << "|";
	std::cout << std::setw(10) << "Last Name" << "|";
	std::cout << std::setw(10) << "Nickname" << std::endl;

	for (int i = 0; i < 8; ++i)
	{
		if (contacts[i].getFirstName().empty())
			break;

		std::cout << std::setw(10) << i + 1 << "|";
		std::string firstName = contacts[i].getFirstName();
		if (firstName.length() > 10)
			firstName = firstName.substr(0, 9) + ".";
		std::cout << std::setw(10) << firstName << "|";

		std::string lastName = contacts[i].getLastName();
		if (lastName.length() > 10)
			lastName = lastName.substr(0, 9) + ".";
		std::cout << std::setw(10) << lastName << "|";

		std::string nickname = contacts[i].getNickname();
		if (nickname.length() > 10)
			nickname = nickname.substr(0, 9) + ".";
		std::cout << std::setw(10) << nickname << std::endl;
	}

	std::string input;
	std::cout << "Enter the index of the contact to display: ";
	std::getline(std::cin, input);

	if (input.empty() || input.find_first_not_of("0123456789") != std::string::npos)
	{
		std::cout << "Invalid index!" << std::endl;
		return;
	}

	int index = atoi(input.c_str());

	if (index < 1 || index > 8 || contacts[index - 1].getFirstName().empty())
	{
		std::cout << "Invalid index!" << std::endl;
	}
	else
	{
		std::cout << "First Name: " << contacts[index - 1].getFirstName() << std::endl;
		std::cout << "Last Name: " << contacts[index - 1].getLastName() << std::endl;
		std::cout << "Nickname: " << contacts[index - 1].getNickname() << std::endl;
		std::cout << "Phone Number: " << contacts[index - 1].getPhoneNumber() << std::endl;
		std::cout << "Darkest Secret: " << contacts[index - 1].getDarkestSecret() << std::endl;
	}
}
