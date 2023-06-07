#include "Question.h"

Question::Question(const std::string& question, const std::vector<std::string>& possibleAnswers, const std::string& correctAnswer) :
	m_question(question), m_possibleAnswers(possibleAnswers), m_correctAnswer(correctAnswer)
{

}

std::string Question::getQuestion() const
{
	return this->m_question;
}

std::vector<std::string> Question::getPossibleAnswers() const
{
	return this->m_possibleAnswers;
}

std::string Question::getCorrectAnswer() const
{
	return this->m_correctAnswer;
}
