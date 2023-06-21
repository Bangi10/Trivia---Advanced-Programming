#pragma once
#include <string>
#include <vector>

class Question
{
public:
	Question() = default;
	Question(const std::string& question, const std::vector<std::string>& possibleAnswers, const std::string& correctAnswer);
	~Question() = default;

	std::string getQuestion() const;
	std::vector<std::string> getPossibleAnswers() const;
	std::string getCorrectAnswer() const;

private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
	std::string m_correctAnswer;
};