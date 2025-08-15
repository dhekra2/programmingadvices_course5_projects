
#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime >
using namespace std;
//enums         
enum enGameChoices { stone = 1, paper = 2, scissor = 3 };  // computer options also could user options  
enum enPossibleWinner { Player1 = 1, Computer = 2, Draw = 3 };

//read nmubers
int RandomNumber(int From, int To) {
	int RandomNumber = rand() % (To - From + 1) + From;
	return RandomNumber;
}

short ReadRoundNumbersFromTo() {
	short RoundNumbers = 1;
	do {
		cout << "How many rounds 1 to 10 do you want play ?  ";
		cin >> RoundNumbers;
	} while (0 > RoundNumbers || RoundNumbers > 10); // or just reverse the < > to save time 

	return RoundNumbers;
}

//structure 
struct stGameResult {

	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enPossibleWinner GameWinner;
	string WinnerName = "";   // why it has initialed and the onther not .  
};
struct stRoundInfo {
	short RoundNumber = 0;
	enGameChoices PlayerChoice;
	enGameChoices ComputerChoice;  // return a digital form 
	enPossibleWinner Winner;
	string WinnerName = "";
};

//text converter
string WinnerName(enPossibleWinner Winner) {
	string arrWinnerName[3] = { "Player1" , "computer" , "No Winner" };
	return arrWinnerName[Winner - 1];
}
string ChoiceName(enGameChoices Choice) {
	string arrGameName[3] = { "stone" , "paper" , "scissor" };
	return arrGameName[Choice - 1];
}

//player entery to enum
enGameChoices ReadPlayerChoice()
{
	short Choice = 1;
	do {
		cout << "chose:  [1]:Stone, [2]:Paper, [3]:Scissors ? ";
		cin >> Choice;

	} while (Choice > 3 || Choice < 1);

	return  (enGameChoices)Choice;
}
enGameChoices ComputerGamechoice()
{
	return enGameChoices(RandomNumber(1, 3));
}

//each round calculation and result
void SetRoundWinnerScreenColor(enPossibleWinner Winner) {
	switch (Winner) {
	case enPossibleWinner::Player1:
		system("color 2F");
		break;
	case enPossibleWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;
	default:
		system("color 6f ");
		break;
	}

}
enPossibleWinner WhoWonTheRound(stRoundInfo RoundInfo) {

	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
	{
		return enPossibleWinner::Draw;
	}
	switch (RoundInfo.PlayerChoice) {
	case enGameChoices::stone:
		if (RoundInfo.ComputerChoice == enGameChoices::scissor)
			return enPossibleWinner::Player1;
		break;
	case enGameChoices::paper:
		if (RoundInfo.ComputerChoice == enGameChoices::stone)
			return enPossibleWinner::Player1;
		break;
	case enGameChoices::scissor:
		if (RoundInfo.ComputerChoice == enGameChoices::paper)
			return enPossibleWinner::Player1;
		break;
	} //if the player dosn't win so the computer win 
	return enPossibleWinner::Computer;
}
void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << " ************ round [ " << RoundInfo.RoundNumber << " ] ************ \n\n";
	cout << "player1 choic " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "computer choic " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "the winner name " << RoundInfo.WinnerName << endl;

	SetRoundWinnerScreenColor(RoundInfo.Winner);
}

//the whole game result
enPossibleWinner WhoWinGame(short Player1WinTimes, short ComputerWinTimes) {
	if (Player1WinTimes == ComputerWinTimes)
		return enPossibleWinner::Draw;
	else if (Player1WinTimes < ComputerWinTimes)
		return enPossibleWinner::Computer;
	else 		return enPossibleWinner::Player1;
}
stGameResult FillGameResult(short Rounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes) {
	stGameResult GameResult;
	GameResult.GameRounds = Rounds;
	GameResult.Player1WinTimes = Player1WinTimes;
	GameResult.ComputerWinTimes = ComputerWinTimes;
	GameResult.DrawTimes = DrawTimes;
	GameResult.GameWinner = WhoWinGame(Player1WinTimes, ComputerWinTimes);
	GameResult.WinnerName = WinnerName(GameResult.GameWinner);

	return GameResult;
}
void ShowFinalGameResults(stGameResult GameResult) {
	cout << " ************ total rounds [ " << GameResult.GameRounds << " ] ************ \n\n";
	cout << "player1 WinTimes : " << GameResult.Player1WinTimes << endl;
	cout << "computer WinTimes : " << GameResult.ComputerWinTimes << endl;
	cout << " DrawTimes : " << GameResult.DrawTimes << endl;
	cout << "the winner name : " << GameResult.WinnerName << endl;

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

//play the game and fill the objective 
stGameResult PlayGame(short Rounds) { // all rounds in one function 

	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= Rounds; GameRound++) {
		cout << "\n Round [" << GameRound << "] begins \n ";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = ComputerGamechoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);
		// after each round claculate the counters 
		if (RoundInfo.Winner == enPossibleWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.Winner == enPossibleWinner::Computer)
			ComputerWinTimes++;
		else DrawTimes++;

		PrintRoundResults(RoundInfo);
	}

	return  FillGameResult(Rounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

// start the game with orgnized function call 
void StartGame() {
	char PlayAgain = 'Y';
	do {
		ResetScreen();
		stGameResult GameResuts = PlayGame(ReadRoundNumbersFromTo());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResuts);
		cout << endl << Tabs(3) << "Do you want to play again ? Y/N ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main() {

	srand((unsigned)time(0));

	StartGame();


	return 0;
}
