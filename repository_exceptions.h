#pragma once
#include <string>
#include <exception>

using namespace std;

class RepositoryException : public std::exception
{
private:
	string message;
public:
	RepositoryException(string message) : message(std::move(message)) {}
	const char* what() const noexcept override  {
		return message.c_str();
	}
};