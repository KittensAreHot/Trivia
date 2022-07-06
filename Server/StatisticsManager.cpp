#include "StatisticsManager.h"
#include "sqlite3.h"


Statistics StatisticsManager::getUserStatistics(std::string username)
{
	Statistics res;
	res.correct_answers = this->m_database->getNumOfCorrectAnswers(username);
	res.avg_answer_time = this->m_database->getPlayerAverageAnswerTime(username);
	res.total_answers = this->m_database->getNumOfTotalAnswers(username);
	res.played_games = this->m_database->getNumOfPlayerGames(username);
	return res;
}


std::vector<Statistics> StatisticsManager::getHighScore()
{
	return this->m_database->getHighScore();
}
