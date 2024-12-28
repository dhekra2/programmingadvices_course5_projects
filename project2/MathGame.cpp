#include <iostream>
#include <cstdlib> 
#include <ctime>
using namespace std;


enum enQuestionLevel { easy = 1, mid = 2, hard = 3, mix = 4 };  
enum enOperationType { Sum = 1, sub = 2, divi = 3, multi = 4, Mix = 5 };
struct QuestionResult {
	short RoundNumber;
	enQuestionLevel Qlevel;


	enOperationType OpType;
	short RightAnswers;
	short WrongAnswers;
};
int RandomNumber(int From, int To) {
	int RandomNumber = rand() % (To - From + 1) + From;
	return RandomNumber;
} // MAY USE JUST THE rand () ; 
enQuestionLevel ReadUserQlevel() {
	short Choice = 1;
	do {
		cout << "Choose: [1] easy, [2] mid, [3] hard, [4] mix ? ";
		cin >> Choice;
	} while (Choice > 4 || Choice < 1);

	return (enQuestionLevel)Choice;
}
enOperationType ReadUserOpLevel() {
	short Choice = 1;
	do {
		cout << "Choose: [1] sum, [2] sub, [3] div, [4] multi, [5] mix ? ";
		cin >> Choice;
	} while (Choice > 5 || Choice < 1);

	return (enOperationType)Choice;
}
short ReadRoundNumbersFromTo() {
	short RoundNumbers;
	cout << "How many Questions do you want to answer? ";
	cin >> RoundNumbers;
	return RoundNumbers;
}
int GenerateQuestion(enQuestionLevel UserChoic) {

	switch (UserChoic)
	{
	case easy:
		return  RandomNumber(1, 50);
		break;
	case mid:
		return  RandomNumber(51, 100);

		break;
	case hard:
		return  RandomNumber(101, 500);
		break;
	case mix:
		return  (RandomNumber(1, 500));
		break;
	}
	return  RandomNumber(1, 50);
}
bool ChechAnswers(int Operad1, int Operad2, char  Operation, int UserAnswer) {
	switch (Operation)
	{
	case '+':
		return  UserAnswer == (Operad1 + Operad2);
	case '-':
		return  UserAnswer == (Operad1 - Operad2);
	case '*':
		return  UserAnswer == (Operad1 * Operad2);
	case '/':
		return   Operad2 != 0 && UserAnswer == (Operad1 / Operad2);

	}
	return UserAnswer == (Operad1 + Operad2);

}
char ShowOpType(enOperationType Optype) {

	if (Optype == 5)
		Optype = (enOperationType)RandomNumber(1, 4);

	switch (Optype)
	{
	case Sum:
		return '+';
		break;
	case sub:  return '-';
		break;
	case divi:    return '/';
		break;
	case multi: return '*';
		break;
	}
	return '+';

}
void SetRoundsScreenColor(int Operad1, int Operad2, bool Checked, char Op) {

	int CorrectResult = 0;

	switch (Op)
	{
	case '+':
		CorrectResult = Operad1 + Operad1; break;
	case '-':
		CorrectResult = Operad1 - Operad2;  break;

	case 'I':
		CorrectResult = Operad1 * Operad2;
		break;

	case '/':	CorrectResult = Operad1 / Operad2;

		break;

	default:
		CorrectResult = 0;  // Default case; you can choose a suitable default operation
	}

	if (Checked) {
		system("color 2F");
		cout << "correct answer :) ";
	}
	else {
		system("color 4F");
		cout << "\a";
		cout << "Wrong answer :) the correct is = " << CorrectResult;
	}
}
QuestionResult StartQuestions(short Rounds) {

	QuestionResult ResultInfo;
	enQuestionLevel Level = ReadUserQlevel();
	enOperationType Optype = ReadUserOpLevel();
	int UserAnswer, rightAnswers = 0, WrongAnswers = 0;
	for (short GameRound = 1; GameRound <= Rounds; GameRound++) {
		cout << "\n Round [" << GameRound << "/" << Rounds << "] begins\n";

		char OpChar = ShowOpType(Optype);
		int sect1 = GenerateQuestion(Level);
		int sect2 = GenerateQuestion(Level);
		cout << sect1 << "\n " << OpChar << "\n " << sect2 << endl << "-----" << endl;

		cin >> UserAnswer;
		bool bolresult = ChechAnswers(sect1, sect2, OpChar, UserAnswer);

		if (bolresult)
		{
			SetRoundsScreenColor(sect1, sect2, bolresult, OpChar);
			rightAnswers++;
		}
		else {
			SetRoundsScreenColor(sect1, sect2, bolresult, OpChar);
			WrongAnswers++;
		}
	}

	ResultInfo.RoundNumber = Rounds;
	ResultInfo.Qlevel = Level;
	ResultInfo.OpType = Optype;
	ResultInfo.RightAnswers = rightAnswers;
	ResultInfo.WrongAnswers = WrongAnswers;

	return ResultInfo;
	// Return a placeholder QuestionResult for now

}
//helpful tool 
string Tabs(short NumberOfTabs) {
	string T = "";
	for (short i = 0; i < NumberOfTabs; i++)
		T += "\t";

	return T;
}
void ResetScreen() {
	system("cls");
	system("color 0F");
}
void ShowGameOverScreen() {
	cout << Tabs(2) << "------------------------------------------\n\n";
	cout << Tabs(2) << "*** G A M E         O V E R *** \n ";
	cout << Tabs(2) << "------------------------------------------\n\n";

}
void ShowFinalGameResults(QuestionResult GameResults) {
	cout << "Game Results:\n";
	cout << "Level: " << GameResults.Qlevel << "\n";
	cout << "Operation Type: " << GameResults.OpType << "\n";
	cout << "Right Answers: " << GameResults.RightAnswers << "\n";
	cout << "Wrong Answers: " << GameResults.WrongAnswers << "\n";
}
void StartGameQuestions() {
	char PlayAgain = 'Y';
	do {
		ResetScreen();
		QuestionResult GameResults = StartQuestions(ReadRoundNumbersFromTo());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);
		cout << "\nDo you want to play again? Y/N ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
	srand((unsigned)time(0));
	StartGameQuestions();
	return 0;
}
