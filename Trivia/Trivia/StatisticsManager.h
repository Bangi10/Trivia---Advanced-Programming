#pragma once
#include <iostream>
#include "json.hpp"
#include <memory>
#include "IDatabase.h"
class StatisticsManager
{
public:
	//both return json dumped strings
	StatisticsManager(const std::shared_ptr<IDatabase> db);
	~StatisticsManager() = default;

	std::string getHighScore() const;
	std::string getUserStatistics(const std::string& username) const;
private:
	std::weak_ptr<IDatabase> m_database;
};