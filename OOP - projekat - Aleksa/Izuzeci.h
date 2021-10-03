#pragma once
#include <exception>
#include <string>

class GUniversal : public std::exception {
	std::string poruka;
public:
	GUniversal(std::string poruka) :poruka(poruka) {}

	const char* what() const override { return poruka.c_str(); }

};