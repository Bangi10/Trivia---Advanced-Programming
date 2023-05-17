#include "StatisticsManager.h"
using json = nlohmann::json;

std::string StatisticsManager::getHighScore() const
{
    return this->m_database->getHighScore();
}

std::string StatisticsManager::getUserStatistics(std::string username) const
{
    json jData;
    jData["PlayerAverageAnswerTime"] = this->m_database->getPlayerAverageAnswerTime(username);
    jData["NumOfCorrectAnswers"] = this->m_database->getNumOfCorrectAnswers(username);
    jData["NumOfTotalAnswers"] = this->m_database->getNumOfTotalAnswers(username);
    jData["NumOfPlayerGames"] = this->m_database->getNumOfPlayerGames(username);
    return jData.dump();
}
