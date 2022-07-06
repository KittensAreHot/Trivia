#pragma once
#include <string>

class Exception {
public:
	Exception(const std::string what) {
		this->msg = what;
	}

	std::string what() const{
		return this->msg;
	}

private:
	std::string msg;
};