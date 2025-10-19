#include "MutantStack.hpp"
#include <iostream>
#include <list>

int main()
{
	std::cout << "=== Testing MutantStack ===" << std::endl;
	MutantStack<int> mstack;

	mstack.push(5);
	mstack.push(17);

	std::cout << "Top element: " << mstack.top() << std::endl;

	mstack.pop();

	std::cout << "Size after pop: " << mstack.size() << std::endl;

	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);

	std::cout << "Elements in MutantStack:" << std::endl;
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();

	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}

	// Test that MutantStack can be used as a std::stack
	std::stack<int> s(mstack);
	std::cout << "std::stack size from MutantStack: " << s.size() << std::endl;

	std::cout << "\n=== Testing with std::list (for comparison) ===" << std::endl;
	std::list<int> lst;

	lst.push_back(5);
	lst.push_back(17);

	std::cout << "Back element: " << lst.back() << std::endl;

	lst.pop_back();

	std::cout << "Size after pop: " << lst.size() << std::endl;

	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	lst.push_back(0);

	std::cout << "Elements in std::list:" << std::endl;
	std::list<int>::iterator lit = lst.begin();
	std::list<int>::iterator lite = lst.end();

	++lit;
	--lit;
	while (lit != lite)
	{
		std::cout << *lit << std::endl;
		++lit;
	}

	std::cout << "\n=== Additional Tests ===" << std::endl;

	// Test copy constructor
	MutantStack<int> mstack2(mstack);
	std::cout << "Copy size: " << mstack2.size() << std::endl;

	// Test assignment operator
	MutantStack<int> mstack3;
	mstack3 = mstack;
	std::cout << "Assignment size: " << mstack3.size() << std::endl;

	// Test with different type
	MutantStack<std::string> strStack;
	strStack.push("Hello");
	strStack.push("World");
	strStack.push("42");

	std::cout << "String stack elements:" << std::endl;
	for (MutantStack<std::string>::iterator sit = strStack.begin();
		 sit != strStack.end(); ++sit)
	{
		std::cout << *sit << std::endl;
	}

	// Test reverse iterators
	std::cout << "Reverse iteration:" << std::endl;
	for (MutantStack<std::string>::reverse_iterator rit = strStack.rbegin();
		 rit != strStack.rend(); ++rit)
	{
		std::cout << *rit << std::endl;
	}

	return 0;
}
