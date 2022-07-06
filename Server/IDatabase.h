#pragma once
#include <string>
#include <list>
#include <vector>
#include "Statistics.h"

typedef struct Question
{
	std::string quesion;
	std::string questionData; //with json representation
} Question;


class IDatabase
{
public:
	// TODO: deal with sql injection 
	virtual bool doesUserExist(const std::string& user) = 0;
	virtual bool doesPasswordMatch(const std::string& password, const std::string& secondPass) = 0;
	virtual void addNewUser(const std::string& username, const std::string& password, const std::string& email) = 0;
	virtual std::list<Question> getQuestions(const int amount) = 0;
	virtual float getPlayerAverageAnswerTime(std::string) = 0;
	virtual int getNumOfCorrectAnswers(std::string) = 0;
	virtual int getNumOfTotalAnswers(std::string) = 0;
	virtual int getNumOfPlayerGames(std::string) = 0;
	virtual std::vector<Statistics> getHighScore() = 0;
};

