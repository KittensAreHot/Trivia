#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <algorithm>
#include <list>


struct calcAvg {
	int amount = 0;
	float sum = 0;
};

class SqliteDatabase : public IDatabase
{
public:

	SqliteDatabase();
	~SqliteDatabase();

	// -- db methods: user
	bool doesUserExist(const std::string& user) override;
	bool doesPasswordMatch(const std::string& username, const std::string& password) override;
	void addNewUser(const std::string& username, const std::string& email, const std::string& password) override;
	// -- db methods: questions
	std::list<Question> getQuestions(const int amount) override;
	// -- db methods: statistics
	float getPlayerAverageAnswerTime(std::string) override;
	int getNumOfCorrectAnswers(std::string) override;
	int getNumOfTotalAnswers(std::string) override;
	int getNumOfPlayerGames(std::string) override;
	std::vector<Statistics> getHighScore() override;

private:

	// -- callbacks
	static int awaitQuery(void* data, int argc, char** argv, char** azColName);
	static int questionQuery(void* data, int argc, char** argv, char** azColName);
	static int calcAvgQuery(void* data, int argc, char** argv, char** azColName);
	static int incrementIntQuery(void* data, int argc, char** argv, char** azColName);
	static int top5gamesQuery(void* data, int argc, char** argv, char** azColName);

	// -- table modifiers
	void createUsersTable();
	void createStatisticsTable();
	bool open();
	void close();

	static std::string toLower(std::string s) {
		std::transform(s.begin(), s.end(), s.begin(),
			[](unsigned char c) { return std::tolower(c); });
		return s;
	}

	sqlite3* db;
};

