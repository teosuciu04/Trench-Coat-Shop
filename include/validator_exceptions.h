#pragma once
#include <string>
#include <exception>
using namespace std;

class ValidationException : public std::exception
{
private:
	string message;
public:
	ValidationException(string message);
	const char* what() const noexcept override;
};