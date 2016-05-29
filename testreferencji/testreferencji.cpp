// testreferencji.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

bool wczytaj_liczbe( int & liczba )
{
    std::cin.clear();
    std::cin.sync();
    std::cin >> liczba;
	std::cout << liczba << std::endl;
    return std::cin.good();
}

int main()
{
    int x;
	std::cout << wczytaj_liczbe(x) << std::endl;

	
	if ((wczytaj_liczbe(x)))
	{
		std::cout << "Poprawnie wpisano liczbe" << std::endl;

	}
	else
	{
		std::cout << "Nie wpisano liczby" << x << std::endl;
	}
    
std::cin >> x;
    return 0;
	
}