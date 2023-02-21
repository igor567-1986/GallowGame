#include<iostream>
#include <iostream>
#include <algorithm>
#include <functional>
#include<vector>


using namespace std;
using std::cin;
using std::cout;
using std::endl;


void GallowsGameStart(const string SECRET_WORD);
void enterCorrectGuess(string* userAnswer, const string correctAnswer, char* userLetter, string* usedLetters, const short playerMistakes);
bool isSmallLetter(const char letter);
char toUpper(char ch);
bool isBigLetter(const char letter);
string enterWord();
bool isWord(const string word);
string wordToWORD(string word);
bool isFinalDecision(const short userAnswerSize, const short correctAnswerSize);
bool isLetterUsed(const string usedLetters, const char letter);
void show(const string usedLetters);
bool isLetterExist(const char letter);
bool isWordExist(const string word);
bool isLetterInWord(const string SECRET_WORD, const char letter);
string addLetterToAnswer(const string SECRET_WORD, const char guess, string userAnswer);
bool isWin(const string answer, const string correctAnswer);
void win(const short mistakes, const string answer);
void lose(const string answer);

void main()
{

	vector<string>Words;
	Words.push_back("ПИЦЦА");
	Words.push_back("ВОЛГА");
	Words.push_back("МОСКВА");
	Words.push_back("ТРАВА");
	Words.push_back("ГОРА");
	Words.push_back("ПИРОГ");

	random_shuffle(Words.begin(), Words.end());
	const string SECRET_WORD = Words[0];
	
	cout << "\t\t\t\t\t\t Игра Виселица" << endl;
	
	int Menu;
	do	{
		cout << "Привет, пользователь.Давай сыграем в игру \"Виселица\", правила которой просты.\n "
			<< " Я, программа, загадываю слово, а ты его отгадываешь по буквам. Если ошибешься десять раз, то проиграешь.\n"
			<< " Слово будет состоять из букв Русского алфавита.\n\n";
		cout << "1 - начиниаем играть" << endl;;
		cout << "0 - выход" << endl;;
		cin >> Menu;
		cin.ignore();
		if (Menu == 1) {
			GallowsGameStart(SECRET_WORD);
		  }
	} while (Menu != 0);
	
}

void GallowsGameStart(const string SECRET_WORD)
{
	short playerMistakes = 0;
	const short MAX_MISTAKES = 10;
	string userAnswer(SECRET_WORD.size(), '-');
	string usedLetters = "";
	char userLetter;

	cout << "\t\tИгра началась!" << endl;

	while (playerMistakes < MAX_MISTAKES)
	{
		enterCorrectGuess(&userAnswer, SECRET_WORD, &userLetter, &usedLetters, playerMistakes);

		if (userAnswer == SECRET_WORD)
		{
			win(playerMistakes, SECRET_WORD);
			break;
		}

		else if (isLetterInWord(SECRET_WORD, userLetter))
		{
			system("cls");
			cout << "Верно, " << userLetter << " есть в слове!" << endl;
			userAnswer = addLetterToAnswer(SECRET_WORD, userLetter, userAnswer);
		}
		else
		{
			system("cls");
			cout << "Неверно, " << userLetter << " нет в слове!" << endl;
			cout << "Количество ошибок = " << ++playerMistakes << endl;
		}

		if (isWin(userAnswer, SECRET_WORD))
		{
			win(playerMistakes, SECRET_WORD);
			break;
		}
	}
	if (playerMistakes == MAX_MISTAKES)
	{
		lose(SECRET_WORD);
	}
}
void enterCorrectGuess(string* userAnswer, const string correctAnswer, char* userLetter, string* usedLetters, const short playerMistakes)
{
	string userWord;

	while (true)
	{
		cout << "Загаданное слово: " << *userAnswer << endl;
		show(*usedLetters);
		userWord = enterWord();

		if (isWord(userWord))
		{
			if (isFinalDecision(userWord.size(), correctAnswer.size()))
			{
				userWord = wordToWORD(userWord);
				if (isWordExist(userWord))
				{
					if (isWin(userWord, correctAnswer))
					{
						*userAnswer = correctAnswer;
						break;
					}
				}
				else
				{
					lose(correctAnswer);
					break;
				}
			}
			else
			{
				system("cls");
				cout << "Нельзя вводить несколько букв за раз!" << endl;
			}
		}
		// буква
		else
		{
			*userLetter = userWord[0];

			if (isLetterExist(*userLetter))
			{
				if (isSmallLetter(*userLetter))
				{
					*userLetter = toUpper(*userLetter);
				}
				if (!isLetterUsed(*usedLetters, *userLetter))
				{
					*usedLetters += *userLetter;
					break;
				}
				else
				{
					system("cls");
					cout << "Вы уже использовали букву " << userLetter << "!" << endl;
				}
			}
			else
			{
				system("cls");
				cout << "Введенная буква отсутствует в русском языке, а значит и в слове!" << userLetter<< endl;
			}
		}
	}
}
string enterWord()
{
	string guess;
	cout << "Введите букву или загаданное слово: ";
	cin >> guess;

	return guess;
}
bool isWord(const string word)
{
	if (word.size() != 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
string wordToWORD(string word)
{
	for (int i = 0; i < word.size(); i++)
	{
		if (isSmallLetter(word[i]))
		{
			word[i] = toUpper(word[i]);
		}
	}
	return word;
}
bool isFinalDecision(const short userAnswerSize, const short correctAnswerSize)
{
	if (userAnswerSize == correctAnswerSize)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool isLetterUsed(const string usedLetters, const char letter)
{
	if (usedLetters.find(letter) == string::npos)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool isSmallLetter(const char letter)//это маленькая буква
{
	if ((letter >= -31 && letter <= -1) || letter == -72)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool isBigLetter(const char letter)//это большая буква
{
	if ((letter >= -64 && letter <= -33) || letter == -88)
	{
		return true;
	}
	else
	{
		return false;
	}
}
char toUpper(char ch)
{
	return (char)(ch - 32);
}
void show(const string usedLetters)
{
	cout << "Вы уже использовали следующие буквы: " << endl;
	cout << usedLetters << endl;
}
bool isLetterExist(const char letter)
{
	if (isSmallLetter(letter))
	{
		return true;
	}
	else if (isBigLetter(letter))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool isWordExist(const string word)//это слово существует
{
	for (int i = 0; i < word.size(); i++)
	{
		if (isSmallLetter(word[i]))
		{
			return false;
		}
	}
	return true;
}
bool isLetterInWord(const string SECRET_WORD, const char letter)//это буква слова
{
	if (SECRET_WORD.find(letter) != string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}
}
string addLetterToAnswer(const string SECRET_WORD, const char guess, string userAnswer)
{
	for (int i = 0; i < SECRET_WORD.length(); ++i)
	{
		if (SECRET_WORD[i] == guess)
		{
			userAnswer[i] = guess;
		}
	}
	return userAnswer;
}
bool isWin(const string answer, const string correctAnswer)
{
	if (answer == correctAnswer)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void win(const short mistakes, const string answer)
{
	cout << "Вы отгадали слово " << answer << " ошибившись " << mistakes << " раз! Поздравляем!" << endl;
}
void lose(const string answer)
{
	cout << "Вы проиграли! Вам обязательно повезёт в следующий раз." << endl;
	cout << "Слово, которое вы не смогли отгадать это: " << answer << endl;
}