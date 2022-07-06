#include "SqliteDatabase.h"
#include "Exceptions.h"
#include "Statistics.h"
#include <io.h>
#include <iostream>
#include <vector>
#include <time.h>


#define CLOSE_DB sqlite3_close(this->db); this->db = nullptr
#define DB_ERROR_MSG_CODE this->db = nullptr;	std::cout << "Couldn't perform the action, error code: " << result << std::endl
#define DB_ERROR_MSG this->db = nullptr;	std::cout << "Couldn't perform the action, error: " << errMessage << std::endl
#define DB_NAME "Trivia.sqlite"

#define TABLE_USERS Users
#define USER_ID User_ID
#define USER_NAME Name
#define USER_PASSWORD Password
#define USER_EMAIL Email

#define TABLE_STATISTICS Statistics
#define STATISTICS_ID ID
#define STATISTICS_USER_ID User_ID
#define STATISTICS_AVG_ANSWER_TIME Avg_answer_time
#define STATISTICS_CORRECT_ANSWERS Correct_answers
#define STATISTICS_TOTAL_ANSWERS Total_answers
#define STATISTICS_PLAYED_GAMES Played_games


#define TABLE_QUESTIONS questions
#define QUESTION_ID id 
#define QUESTION_CONTENT question 
#define QUESTION_DATA questionData 

#define MAX_QUESTIONS 1000


SqliteDatabase::SqliteDatabase()
{
	// try open database on ctor
	if (!this->open()) {
		throw Exception("Couldn't open database");
	}
}

SqliteDatabase::~SqliteDatabase()
{
	// close database on ctor
	this->close();
}

bool SqliteDatabase::doesUserExist(const std::string& user)
{
	bool doesExist = false;

	std::string sqlStatement = "SELECT * FROM TABLE_USERS WHERE TABLE_USERS.USER_NAME = \"" + user + "\";";

	char* errMessage = nullptr;

	int res = sqlite3_exec(this->db, sqlStatement.c_str(), awaitQuery, &doesExist, &errMessage);
	if (res != SQLITE_OK) {
		throw Exception("Couldn't search for the given user. error message: \n" + std::string(errMessage));
	}
	return doesExist;
}

bool SqliteDatabase::doesPasswordMatch(const std::string& username, const std::string& password)
{
	bool doesMatch = false;

	std::string sqlStatement = "SELECT * FROM TABLE_USERS WHERE TABLE_USERS.USER_NAME = \"" + username + "\" AND TABLE_USERS.USER_PASSWORD = " + password + ";";

	char* errMessage = nullptr;

	int res = sqlite3_exec(this->db, sqlStatement.c_str(), awaitQuery, &doesMatch, &errMessage);
	if (res != SQLITE_OK) {
		throw Exception("Couldn't search for a matching password. error message: \n" + std::string(errMessage));
	}
	return doesMatch;
}

void SqliteDatabase::addNewUser(const std::string& username,  const std::string& email, const std::string& password)
{
	std::string sqlStatement = "INSERT INTO TABLE_USERS (USER_NAME, USER_EMAIL, USER_PASSWORD) values "\
		"(\"" + username + "\", \"" + email + "\", \"" + password + "\")";
	char* errMessage = nullptr;

	int result = sqlite3_exec(this->db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
	if (result != SQLITE_OK) {
		throw Exception("Couldn't add user... error message: \n" + std::string(errMessage));
	}
}

std::list<Question> SqliteDatabase::getQuestions(const int amount)
{
	srand((unsigned int)time(NULL));
	std::list<Question> questions;
	std::vector<int> questionIds;
	for (int i = 0; i < amount; i++) {
		int id = rand() % MAX_QUESTIONS;
		while (std::find(questionIds.begin(), questionIds.end(), id) != questionIds.end()) {
			id = rand() % MAX_QUESTIONS;
		}
		questionIds.push_back(id);
	}
	
	for (int i = 0; i < amount; i++) {
		std::string sqlStatement = "SELECT * FROM TABLE_QUESTIONS WHERE TABLE_QUESTIONS.QUESTION_ID = " + std::to_string(questionIds[i]) + ";";
		char* errMessage = nullptr;

		int res = sqlite3_exec(this->db, sqlStatement.c_str(), questionQuery, &questions, &errMessage);
		if (res != SQLITE_OK) {
			throw Exception("Couldn't get questions... error message: \n" + std::string(errMessage));
		}
	}

	return questions;
}


int SqliteDatabase::awaitQuery(void* data, int argc, char** argv, char** azColName)
{
	bool* exists = (bool*)data;
	*exists = true;
	return 0;
}

int SqliteDatabase::questionQuery(void* data, int argc, char** argv, char** azColName)
{
	std::list<Question>* questions = (std::list<Question>*)data;
	Question question;
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[i]) == "QUESTION_CONTENT") {
			question.quesion = argv[i];
		}
		else if (std::string(azColName[i]) == "QUESTION_DATA") {
			question.questionData = argv[i];
		}
	}
	questions->push_back(question);
	return 0;
}


void SqliteDatabase::createUsersTable()
{
	std::string sqlStatement = "CREATE TABLE TABLE_USERS(USER_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, USER_NAME Text NOT NULL, USER_PASSWORD Text NOT NULL, USER_EMAIL Text NOT NULL);";
	char* errMessage = nullptr;

	int result = sqlite3_exec(this->db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
	if (result != SQLITE_OK) {
		std::cout << "CRITICAL ERROR: Failed to define user database" << std::endl;
		DB_ERROR_MSG;
		this->close();
		std::exit(1);
	}
}


void SqliteDatabase::createStatisticsTable()
{
	std::string sqlStatement = "CREATE TABLE TABLE_STATISTICS(STATISTICS_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, STATISTICS_TOTAL_ANSWERS INTEGER NOT NULL, STATISTICS_CORRECT_ANSWERS INTEGER NOT NULL, STATISTICS_PLAYED_GAMES INTEGER NOT NULL, STATISTICS_AVG_ANSWER_TIME FLOAT NOT NULL, STATISTICS_USER_ID INTEGER NOT NULL, FOREIGN KEY (STATISTICS_USER_ID) REFERENCES TABLE_USERS(USER_ID));";
	char* errMessage = nullptr;

	int result = sqlite3_exec(this->db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
	if (result != SQLITE_OK) {
		std::cout << "CRITICAL ERROR: Failed to define statistics database" << std::endl;
		DB_ERROR_MSG;
		this->close();
		std::exit(1);
	}
}


bool SqliteDatabase::open()
{
	std::string dbFilePath = DB_NAME;

	// opening/creating the database
	int fileExists = _access(dbFilePath.c_str(), 0);
	int result = sqlite3_open(dbFilePath.c_str(), &(this->db));
	if (result != SQLITE_OK) {
		DB_ERROR_MSG_CODE;
		return false;
	}
	// Database opened succefully!
	if (fileExists == -1) { 
		// -- if file doesnt exist, we need to configure the tables
		this->createUsersTable();
		this->createStatisticsTable();
	}
	return true;
}

void SqliteDatabase::close()
{
	CLOSE_DB;
}


// db statistics methods

int SqliteDatabase::calcAvgQuery(void* data, int argc, char** argv, char** azColName)
{
	calcAvg* ans = (calcAvg*)data;
	if (argv && argv[0]) {
		ans->sum += std::stof(argv[0]);
		ans->amount += 1;
	}
	return 0;
}

int SqliteDatabase::incrementIntQuery(void* data, int argc, char** argv, char** azColName)
{
	int* ans = (int*)data;
	*ans += 1;
	return 0;
}

float SqliteDatabase::getPlayerAverageAnswerTime(std::string username)
{
	std::string sqlStatement = "SELECT TABLE_STATISTICS.STATISTICS_AVG_ANSWER_TIME FROM STATISTICS INNER JOIN TABLE_USERS ON TABLE_USERS.USER_ID = TABLE_STATISTICS.STATISTICS_USER_ID Where TABLE_USERS.USER_NAME = " + username + ";";
	char* errMessage = nullptr;
	calcAvg ans;

	int result = sqlite3_exec(this->db, sqlStatement.c_str(), calcAvgQuery, &ans, &errMessage);
	if (result != SQLITE_OK)
		throw Exception("ERROR: Couldn't find average answer time stat");
	else return ans.sum / ans.amount;
}


int SqliteDatabase::getNumOfCorrectAnswers(std::string username)
{
	std::string sqlStatement = "SELECT TABLE_STATISTICS.STATISTICS_CORRECT_ANSWERS FROM STATISTICS INNER JOIN TABLE_USERS ON TABLE_USERS.USER_ID = TABLE_STATISTICS.STATISTICS_USER_ID Where TABLE_USERS.USER_NAME = " + username + ";";
	char* errMessage = nullptr;
	int ans = 0;

	int result = sqlite3_exec(this->db, sqlStatement.c_str(), incrementIntQuery, &ans, &errMessage);
	if (result != SQLITE_OK)
		throw Exception("ERROR: Couldn't find correct answers stat");
	else return ans;
}


int SqliteDatabase::getNumOfTotalAnswers(std::string username)
{
	std::string sqlStatement = "SELECT TABLE_STATISTICS.STATISTICS_TOTAL_ANSWERS FROM STATISTICS INNER JOIN TABLE_USERS ON TABLE_USERS.USER_ID = TABLE_STATISTICS.STATISTICS_USER_ID Where TABLE_USERS.USER_NAME = " + username + ";";
	char* errMessage = nullptr;
	int ans = 0;

	int result = sqlite3_exec(this->db, sqlStatement.c_str(), incrementIntQuery, &ans, &errMessage);
	if (result != SQLITE_OK)
		throw Exception("ERROR: Couldn't find total answers stat");
	else return ans;
}


int SqliteDatabase::getNumOfPlayerGames(std::string username)
{
	std::string sqlStatement = "SELECT TABLE_STATISTICS.STATISTICS_PLAYED_GAMES FROM STATISTICS INNER JOIN TABLE_USERS ON TABLE_USERS.USER_ID = TABLE_STATISTICS.STATISTICS_USER_ID Where TABLE_USERS.USER_NAME = " + username + ";";
	char* errMessage = nullptr;
	int ans = 0;

	int result = sqlite3_exec(this->db, sqlStatement.c_str(), incrementIntQuery, &ans, &errMessage);
	if (result != SQLITE_OK)
		throw Exception("ERROR: Couldn't find amount of played games stat");
	else return ans;
}


int SqliteDatabase::top5gamesQuery(void* data, int argc, char** argv, char** azColName)
{
	Statistics stats = {0, 0, 0, 0.0f};
	std::vector<Statistics>* list = (std::vector<Statistics>*)data;
	// sort fields
	for (int i = 0; i < argc; i++)
	{
		if (azColName[i] && std::string(azColName[i]) == "STATISTICS_AVG_ANSWER_TIME")
			stats.avg_answer_time = std::stof(argv[i]);
		else if (azColName[i] && std::string(azColName[i]) == "STATISTICS_CORRECT_ANSWERS")
			stats.correct_answers = std::atoi(argv[i]);
		else if (azColName[i] && std::string(azColName[i]) == "STATISTICS_PLAYED_GAMES")
			stats.played_games = std::atoi(argv[i]);
		else if (azColName[i] && std::string(azColName[i]) == "STATISTICS_TOTAL_ANSWERS")
			stats.total_answers = std::atoi(argv[i]);
	}
	list->push_back(stats);
	return 0;
}


std::vector<Statistics> SqliteDatabase::getHighScore()
{
	char* errMessage = nullptr;
	std::vector<Statistics> top5;
	std::string sqlStatement = "SELECT STATISTICS_TOTAL_ANSWERS, STATISTICS_CORRECT_ANSWERS, STATISTICS_PLAYED_GAMES, STATISTICS_AVG_ANSWER_TIME, STATISTICS_USER_ID FROM TABLE_STATISTICS ORDER BY STATISTICS_CORRECT_ANSWERS LIMIT 5;";

	int result = sqlite3_exec(this->db, sqlStatement.c_str(), this->top5gamesQuery, (void*)&top5, &errMessage);
	if (result != SQLITE_OK) {
		throw Exception("Unexpected error while searching for statistics");
	}
	return top5;
}

