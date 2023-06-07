#pragma once
#include <vector>
#include <string>
#include "json.hpp"
#include "IDatabase.h"
#include <memory>

class StatisticsManager
{
public:
	//both return json dumped strings
	StatisticsManager(std::shared_ptr<IDatabase>& db);
	~StatisticsManager() = default;

	std::string getHighScores() const;
	std::string getUserStatistics(const std::string& username) const;
private:
	std::weak_ptr<IDatabase> m_database;
};