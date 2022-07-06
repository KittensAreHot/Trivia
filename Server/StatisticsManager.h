#pragma once
#include "SqliteDatabase.h"
#include "Statistics.h"
#include <string>
#include <vector>


class StatisticsManager {
private:
	SqliteDatabase* m_database;
public:
	// get statistics from DB
	std::vector<Statistics> getHighScore();
	Statistics getUserStatistics(std::string username);
};
