#include "validator_exceptions.h"
#include <utility>

ValidationException::ValidationException(string message)
{
	this->message = message;
}

const char* ValidationException::what() const noexcept
{
	return message.c_str();
}
