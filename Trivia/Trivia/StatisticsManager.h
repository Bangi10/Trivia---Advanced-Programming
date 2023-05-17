#pragma once
#include <vector>
#include <iostream>
#include "json.hpp"

class StatisticsManager
{
public:
	//both return json dumped strings
	std::string getHighScore() const;
	std::string getUserStatistics(std::string username) const;
private:
	IDatabase* m_database;
};