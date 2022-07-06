#pragma once
#include <string>


typedef struct Question {
	std::string question;
	std::string answers[4];
	unsigned int right_answer;	// 0-3
} Question;
