#pragma once
#include <string>
#include "Question.h"

struct GameData {
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;

};
