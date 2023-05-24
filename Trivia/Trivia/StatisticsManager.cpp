#include "StatisticsManager.h"
using json = nlohmann::json;

StatisticsManager::StatisticsManager(const std::shared_ptr<IDatabase> db)
{
    this->m_database = db;
}

std::string StatisticsManager::getHighScore() const
{
    auto shared = m_database.lock();
    return shared->getHighScore();
}

std::string StatisticsManager::getUserStatistics(const std::string& username) const
{
    auto shared = m_database.lock();
    json jData;
    jData["PlayerAverageAnswerTime"] = shared->getPlayerAverageAnswerTime(username);
    jData["NumOfCorrectAnswers"] = shared->getNumOfCorrectAnswers(username);
    jData["NumOfTotalAnswers"] = shared->getNumOfTotalAnswers(username);
    jData["NumOfPlayerGames"] = shared->getNumOfPlayerGames(username);
    return jData.dump();
}
