#include "StatisticsManager.h"
#include <vector>
using json = nlohmann::json;

StatisticsManager::StatisticsManager(std::shared_ptr<IDatabase>& db) : m_database(db)
{
}

std::string StatisticsManager::getHighScores() const
{
    auto shared = m_database.lock();
    return shared->getHighScores();
}

std::string StatisticsManager::getUserStatistics(const std::string& username) const
{
    auto shared = m_database.lock();
    json jData;
    jData["PlayerAverageAnswerTime"] = shared->getPlayerAverageAnswerTime(username);
    jData["NumOfCorrectAnswers"] = shared->getNumOfCorrectAnswers(username);
    jData["NumOfTotalAnswers"] = shared->getNumOfTotalAnswers(username);
    jData["NumOfPlayedGames"] = shared->getNumOfPlayedGames(username);
    return jData.dump();
}
