#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enQuestionsLevel { Easy = 1, Medium = 2, Hard = 3, Mix = 4 };
enum enQuestionsOperationType { Add = 1, Sub = 2, Multi = 3, Div = 4, MixOp = 5 };

struct stMathQuestion {
    enQuestionsLevel QuestionLevel;
    enQuestionsOperationType OpType;
    int Num1 = 0;
    int Num2 = 0;
    int PlayerAnswer = 0;
    int CorrectAnswer = 0;
    bool IsCorrectAnswer = false;
};

struct stMathQuizz {
    stMathQuestion QuestionList[50];
    enQuestionsLevel QuestionLevel1;
    enQuestionsOperationType OpType1;
    short NumOfQuestions = 0;
    short NumWrongAnswers = 0;
    short NumRightAnswers = 0;
    bool Ispass = false;
};

int RandomNumber(int from, int to) {
    return rand() % (to - from + 1) + from;
}

int SimpleCalculator(int Num1, int Num2, enQuestionsOperationType OpType) {
    switch (OpType) {
    case Add: return (Num1 + Num2);
    case Sub: return (Num1 - Num2);
    case Multi: return (Num1 * Num2);
    case Div: return (Num2 != 0) ? (Num1 / Num2) : 1; // Prevent division by zero
    default: return Num1 + Num1;
    }
}

void ResetScreen() {
#ifdef _WIN32
    system("cls");
    system("color 0F");
#else
    system("clear");
#endif
}

void SetScreenColor(bool Right) {
    if (Right) {
#ifdef _WIN32
        system("color 2F"); // Green for correct answers
#endif
    }
    else {
#ifdef _WIN32
        system("color 4F"); // Red for incorrect answers
#endif
        cout << "\a"; // Alert sound
    }
}

string Tabs(short NumberOfTabs) {
    string T = "";
    for (short i = 0; i < NumberOfTabs; i++)
        T += "\t";
    return T;
}

void ShowGameOverScreen() {
    cout << Tabs(2) << "------------------------------------------\n\n";
    cout << Tabs(2) << "*** G A M E         O V E R *** \n ";
    cout << Tabs(2) << "------------------------------------------\n\n";
}

short ReadQuestionNumbersFromTo() {
    short QuesNumbers;
    do {
        cout << "How many questions (1 to 50) do you want to play? ";
        cin >> QuesNumbers;
    } while (QuesNumbers < 1 || QuesNumbers > 50);
    return QuesNumbers;
}

int ReadQuestionUserAnswer() {
    int Answer;
    cin >> Answer;
    return Answer;
}

enQuestionsLevel ReadUserQlevel() {
    short Choice;
    do {
        cout << "Choose: [1] easy, [2] mid, [3] hard, [4] mix ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 4);
    return (enQuestionsLevel)Choice;
}

string GetQuestionTextLevel(enQuestionsLevel questionlevel) {
    string ArrQuestionLevelText[4] = { "Easy", "Medium", "Hard", "Mix" };
    return ArrQuestionLevelText[questionlevel - 1];
}

enQuestionsOperationType ReadUserOpLevel() {
    short Choice;
    do {
        cout << "Choose: [1] sum, [2] sub, [3] multi, [4] div, [5] mix ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 5);
    return (enQuestionsOperationType)Choice;
}

char GetOperationType(enQuestionsOperationType OpType) {
    switch (OpType) {
    case Add: return '+';
    case Sub: return '-';
    case Multi: return '*';
    case Div: return '/';
    }
}

stMathQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enQuestionsOperationType OpType) {
    stMathQuestion Question;

    // Determine level
    if (QuestionLevel == Mix)
        Question.QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
    else
        Question.QuestionLevel = QuestionLevel;

    // Determine operation
    if (OpType == MixOp)
        Question.OpType = (enQuestionsOperationType)RandomNumber(1, 4);
    else
        Question.OpType = OpType;

    // Assign numbers based on level
    switch (Question.QuestionLevel) {
    case Easy:
        Question.Num1 = RandomNumber(1, 10);
        Question.Num2 = RandomNumber(1, 10);
        break;
    case Medium:
        Question.Num1 = RandomNumber(10, 50);
        Question.Num2 = RandomNumber(10, 50);
        break;
    case Hard:
        Question.Num1 = RandomNumber(50, 100);
        Question.Num2 = RandomNumber(50, 100);
        break;
    }

    // Prevent division by zero
    if (Question.OpType == Div && Question.Num2 == 0)
        Question.Num2 = 1;

    Question.CorrectAnswer = SimpleCalculator(Question.Num1, Question.Num2, Question.OpType);
    return Question;
}

void GenerateQuizzQuestions(stMathQuizz& Quizz) {
    for (short i = 0; i < Quizz.NumOfQuestions; i++) {
        Quizz.QuestionList[i] = GenerateQuestion(Quizz.QuestionLevel1, Quizz.OpType1);
    }
}

void PrintQuestion(stMathQuizz& Quizz, short QuestionIndex) {
    cout << "\nQuestion [" << QuestionIndex + 1 << "/" << Quizz.NumOfQuestions << "]\n";
    cout << Quizz.QuestionList[QuestionIndex].Num1 << endl;
    cout << GetOperationType(Quizz.QuestionList[QuestionIndex].OpType) << endl;
    cout << Quizz.QuestionList[QuestionIndex].Num2 << endl;
    cout << "__________" << endl;
}

void CorrectQuestionAnswer(stMathQuizz& Quizz, short QuestionIndex) {
    if (Quizz.QuestionList[QuestionIndex].PlayerAnswer != Quizz.QuestionList[QuestionIndex].CorrectAnswer) {
        Quizz.QuestionList[QuestionIndex].IsCorrectAnswer = false;
        Quizz.NumWrongAnswers++;
        cout << "Wrong answer! The correct answer is " << Quizz.QuestionList[QuestionIndex].CorrectAnswer << endl;
    }
    else {
        Quizz.QuestionList[QuestionIndex].IsCorrectAnswer = true;
        Quizz.NumRightAnswers++;
        cout << "Correct answer! :)\n";
    }
    SetScreenColor(Quizz.QuestionList[QuestionIndex].IsCorrectAnswer);
}

void AskAndCorrectQuestionListsAnswers(stMathQuizz& Quizz) {
    for (short i = 0; i < Quizz.NumOfQuestions; i++) {
        PrintQuestion(Quizz, i);
        Quizz.QuestionList[i].PlayerAnswer = ReadQuestionUserAnswer();
        CorrectQuestionAnswer(Quizz, i);
    }
    Quizz.Ispass = (Quizz.NumRightAnswers >= Quizz.NumWrongAnswers);
}

void PrintQuizzResult(stMathQuizz Quizz) {
    cout << "\n***********************************\n";
    cout << "Final Result: " << (Quizz.Ispass ? "Pass ;)" : "Fail ;(") << endl;
    cout << "***********************************\n";
    cout << "Total Questions: " << Quizz.NumOfQuestions << endl;
    cout << "Correct Answers: " << Quizz.NumRightAnswers << endl;
    cout << "Wrong Answers: " << Quizz.NumWrongAnswers << endl;
}

void PlayMathGame() {
    stMathQuizz Quizz;
    Quizz.NumOfQuestions = ReadQuestionNumbersFromTo();
    Quizz.QuestionLevel1 = ReadUserQlevel();
    Quizz.OpType1 = ReadUserOpLevel();
    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionListsAnswers(Quizz);
    PrintQuizzResult(Quizz);
}

int main() {
    cout << "version2 \n"; 
    srand(time(0));
    PlayMathGame();
    return 0;
}
