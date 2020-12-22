#include <iostream>
#include <time.h>
#include <cstring>
#include <string>
#include <locale.h>
#include <Windows.h>
#include <cstdio>
#include <stdlib.h>


using namespace std;



class Card {
private:
	int number; // -1 - Reverse;  -2 -Draw Two; -3 - Skip;(black) -4 -Draw Four; -5 -Color
	int color; // 1-red 2-blue 3-green 4-yellow 0-black
	int cost; // чем больше, тем больше приоретет кинуть 
public:
	Card() { // конструктор по умол.
		number = 0;
		color = 0;
		cost = 0;
	}
	void set(int color, int number) {
		this->color = color;
		this->number = number;

	}

	Card(const  Card& cr) { // конструктор копиров.
		number = cr.number;
		color = cr.color;
		cost = cr.cost;
	}

	void setCost(int cost) {
		this->cost = cost;
	}

	~Card() {

	}
	
	friend void setDefCost(Card& card);
	friend void cardOutput(Card& card);
	friend void randomCard(Card& card);
	friend bool checkCard(Card& mainCard, Card& card);
	friend void moveCard(Card& mainCard, Card& card);
	friend int returnNumber(Card& card);
	friend int returnColor(Card& card);
	friend int returnCost(Card& card);
};

void setDefCost(Card& card) {
	card.cost = 0;
	if (card.number >= 0) { // 0-9
		card.cost = 1000;
	}
	if (card.number==-1 || card.number == -3) { // Reverse, Skip
		card.cost = 800;
	}
	if (card.number == -2) { // +2
		card.cost = 700;
	}
	if (card.number == -4) { // +4
		card.cost = 400;
	}
	if (card.number == -5) { // black color
		card.cost = 600;
	}
}


void cardOutput(Card& card) {
	switch (card.color) {
	case 0: // 0-black
		cout << "black ";
		break;
	case 1: // 1-red 
		cout << "red ";
		break;
	case 2: // 2-blue 
		cout << "blue ";
		break;
	case 3: // 3-green 
		cout << "green ";
		break;
	case 4: // 4-yellow 
		cout << "yellow ";
		break;
	default:
		cout << card.color;
		break;
	}
	if (card.number >= 0) {
		cout << card.number;
	}
	else
	{
		switch (card.number) {
			//-1 - Reverse;  -2 - Draw Two; -3 - Skip;(black) -4 -Draw Four; -5 -Color
		case -1: // -1 - Reverse
			cout << "reverse";
			break;
		case -2: // -2 - Draw Two
			cout << "+2";
			break;
		case -3: // -3 - Skip 
			cout << "skip";
			break;
		case -4: // -4 - Draw Four
			cout << "+4";
			break;
		case -5: // -5 - Color 
			cout << "color";
			break;
		default:
			cout << "";
			break;
		}
	}
	cout << "  ";
};

void randomCard(Card& card) { // простой радном карт
	int color, number, random;
	random = rand() % 54 + 1; // 54 видов карт
	if (random >= 1 && random <= 13) {
		color = 1;
		card.color = color;
		number = rand() % 13 - 3;
		card.number = number;
	}
	if (random >= 14 && random <= 26) {
		color = 2;
		card.color = color;
		number = rand() % 13 - 3;
		card.number = number;
	}
	if (random >= 27 && random <= 39) {
		color = 3;
		card.color = color;
		number = rand() % 13 - 3;
		card.number = number;
	}
	if (random >= 40 && random <= 52) {
		color = 4;
		card.color = color;
		number = rand() % 13 - 3;
		card.number = number;
	}
	if (random >= 53 && random <= 54) {
		color = 0;
		card.color = color;
		number = rand() % 2 - 5;
		card.number = number;
	}

	card.set(color, number);
}

bool checkCard(Card& mainCard, Card& card) { // сравниваем две карты
	bool check=false;
	if (card.color == 0) {
		check = true;
	}
	if (mainCard.number == card.number) {
		check = true;
	}
	else {
		if (mainCard.color == card.color) {
			check = true;
		}
	}
	return check;
}
// friend void moveCard(Card& mainCard,Card& card);

void moveCard(Card& mainCard, Card& card) {
	mainCard.color = card.color;
	mainCard.number = card.number;
}

int returnNumber(Card& card) {
	return card.number;
};

int returnColor(Card& card) {
	return card.color;
};

int returnCost(Card& card) {
	return card.cost;
};


int correctinput() {
	int i,t,b;
	bool a=true;
	string temp;
	do
	{
		getline(cin, temp);
		t = 0;
		for (i = 0; i < temp.length(); i++) {
			if ((int)temp[i]< (int) '0' || (int)temp[i] > (int)'9') {
				cout << "Error!" << endl;
				a = true;
				break;
			}
			else {
				t++;
				a = false;
			}
		}
		if (a == false && t == temp.length()) { b = atoi(temp.c_str()); }
		else {
			a = true;
		}
	} while (a);
	return b;
};




// 1 - red; 2 - blue; 3 - green; 4 - yellow; 0 - black;
//-1 - Reverse;  -2 - Draw Two; -3 - Skip;(black) -4 -Draw Four; -5 -Color

class Player {
public:
	int i, qcard =5; // количество карт в руке
	int arr[4] = {0,0,0,0};
	Card  *card = new Card[qcard];

	void set() {
		for (i = 0; i < qcard; i++) {
			randomCard(card[i]);
		}
	}
	void takecard() {
		Card* temp = new Card[qcard];
		for (i = 0; i < qcard; i++) {
			temp[i] = card[i];
		}
		delete[]card;
		qcard++;
		card = new Card[qcard];
		for (i = 0; i < qcard-1; i++) {
			card[i] = temp[i];
		}
		randomCard(card[qcard-1]);
		delete[]temp;
	}
	void deletecard(int deli) { // Card& delcard,
		for (i = deli; i < qcard; i++) {
			card[i-1] = card[i];
		}
		qcard--;
		Card* temp = new Card[qcard];
		for (i = 0; i < qcard; i++) {
			temp[i] = card[i];
		}
		delete[]card;
		card = new Card[qcard];
		for (i = 0; i < qcard ; i++) {
			card[i] = temp[i];
		}
		delete[]temp;
	}

	~Player() {
		delete[]card;

	}
};

void allInfo(Player& pl, Player& bot, Card& maincard) {
	int i;
	cout << "BOT:\n";
	for (i = 0; i < bot.qcard; i++) {
		cardOutput(bot.card[i]);
	}
	cout << endl << endl;
	cardOutput(maincard);
	cout << endl << endl;
	cout << "YOU:\n";
	for (i = 0; i < pl.qcard; i++) {
		cardOutput(pl.card[i]);
	}
	cout << endl;
};

int whcardmore(Player& bot) { //1-red 2-blue 3-green 4-yellow
	int i = 0, imax, colorcostmax=0, k = 1;
	int colorcost[4] = {0,0,0,0};
	for (i = 0; i < bot.qcard; i++) {
		if (returnColor(bot.card[i]) == 1) {
			colorcost[0] = colorcost[0] + 100;
			if (bot.arr[0]) {
				colorcost[0] = colorcost[0] + 1000;
			}
		}
		if (returnColor(bot.card[i]) == 2) {
			colorcost[1] = colorcost[1] + 100;
			if (bot.arr[1]) {
				colorcost[1] = colorcost[1] + 1000;
			}
		}
		if (returnColor(bot.card[i]) == 3) {
			colorcost[2] = colorcost[2] + 100;
			if (bot.arr[2]) {
				colorcost[2] = colorcost[2] + 1000;
			}
		}
		if (returnColor(bot.card[i]) == 4) {
			colorcost[3] = colorcost[3] + 100;
			if (bot.arr[3]) {
				colorcost[3] = colorcost[3] + 1000;
			}
		}
	}
	imax = 0;
	colorcostmax = colorcost[0];
	for (i = 1; i < 4; i++) {
		if (colorcostmax < colorcost[i]) {
			imax = i;
			colorcostmax = colorcost[i];
		}
	}
	imax++;
	k = imax;
	return k;
};

void botselectcolor(Player& bot) {
	cout << " bot select new color:";
	switch (whcardmore(bot)) {
	case 1:
		cout << "red ";
		break;
	case 2:
		cout << "blue ";
		break;
	case 3:
		cout << "green ";
		break;
	case 4:
		cout << "yellow ";
		break;
	}
	cout << "\n";
};

//-1 - Reverse;  -2 - Draw Two; -3 - Skip;(black) -4 -Draw Four; -5 -Color
bool checkActivity(Player& pl, Player& bot, Card& card, bool player) { // если карта игрока тогда player = true, если бота, то player =false
	int k,i;
	bool check = false,a=true;
	if (returnNumber(card)==-5) {
		if(player){
		cout << "select new color(1-red 2-blue 3-green 4-yellow): ";
		do {
			k = correctinput();
			if (k >= 1 && k <= 4) { a = false; }
			else { cout << "Error!"; }
		} while (a);
		card.set(k,-5);
		}
		else {
			botselectcolor(bot); // каких карт у бота больше такой и цвет
			card.set(whcardmore(bot), -5); 
		}
	}
	if (returnNumber(card) == -4) {
		check = true; // пропуск ходя противника
		if(player){
		cout << "select new color(1-red 2-blue 3-green 4-yellow): ";
		do {

			k = correctinput();
			if (k >= 1 && k <= 4) { a = false; }
			else { cout << "Error!"; }
		} while (a);
		card.set(k, -4);
		cout << "your opponent draws 4 cards\n";
		for (i = 0; i < 4; i++) {
			cout << "bot take a card: ";
			bot.takecard();
			cardOutput(bot.card[bot.qcard - 1]);
			cout << "\n";
		}
		}
		else {
			botselectcolor(bot); // каких карт у бота больше такой и цвет
			card.set(whcardmore(bot), -4);
			cout << "you draws 4 cards\n";
			for (i = 0; i < 4; i++) {
				cout << "you take a card: ";
				pl.takecard();
				cardOutput(pl.card[pl.qcard - 1]);
				cout << "\n";
			}
		}
	}
	if (returnNumber(card) == -3) {
		check = true;
		if (player){
		cout << "your opponent skip a turn\n";
		}
		else {
			cout << "you missed the move\n";
		}
		}
	if (returnNumber(card) == -2) {
		check = true;
		if (player) {
			cout << "your opponent draws 2 cards\n";
			for (i = 0; i < 2; i++) {
				cout << "bot take a card: ";
				bot.takecard();
				cardOutput(bot.card[bot.qcard - 1]);
				cout << "\n";
			}
		}
		else {
			cout << "you draws 2 cards\n";
			for (i = 0; i < 2; i++) {
				cout << "you take a card: ";
				pl.takecard();
				cardOutput(pl.card[pl.qcard - 1]);
				cout << "\n";
			}
		}
	}
	if (returnNumber(card) == -1) { 
		check = true;
		if (player) {
			cout << "your opponent skip a turn\n";
		}
		else {
			cout << "you missed the move\n";
		}
	}
	return check;

};

void changeCost(Player& bot, Player& pl, Card& card, Card& maincard) {
	{
		int i;
		
		if (returnColor(card) == returnColor(maincard) || returnNumber(card) == returnNumber(maincard) || returnColor(card) == 0){
		if (returnNumber(card) >= 0 && bot.arr[returnColor(card) - 1] == 1) { // 0-9 // если в руке противника нету карт данного цвета
			if (pl.qcard == 1) card.setCost(1600);
			if (pl.qcard > 1) card.setCost(900);
		}
		if (returnNumber(card) == -1 || returnNumber(card) == -3) { // Reverse, Skip

			if (pl.qcard == 1) card.setCost(1700);
		}
		if (returnNumber(card) == -2) { // +2
			if (pl.qcard == 1) card.setCost(1800);
		}
		if (returnNumber(card) == -4) { // +4
			if (pl.qcard == 1) card.setCost(1500);
		}
		} else {  card.setCost(-1000); }
	}
}

bool youselect(Player& pl, Player& bot, Card& maincard) {
	// твой ход
	int i,k;
	bool takecheck = true;
	string take;
	bool check=false, game=true, checkAct=false;
	for (i = 0; i < pl.qcard; i++) { // проверяем есть ли в руке карты, которыми можно ходить
		check = checkCard(maincard, pl.card[i]);
		if (check) {
			break;
		}
	}
	if (!check) { // если нет карт, которыми можно ходить предлагается взять карту
		while (takecheck){
			cout << "take a card(\"take\")\n";
		cin >> take; // введите "take"
		if (take == "take") {
			takecheck = false;
		}
		else { cout << "Error!\n"; }
		}
		if (returnColor(maincard)!=0){
		bot.arr[returnColor(maincard)-1]=1; // бот запоминает, что у игрока нету карт такого цвета
		}

		cout << "player take a card: ";
		pl.takecard();
		Sleep(2000);
		cardOutput(pl.card[pl.qcard - 1]);
		Sleep(2000);
		cout << "\n";
		check = checkCard(maincard, pl.card[pl.qcard - 1]);
	
		if (check) { // проверка можно ли ходить взятой картой
			allInfo(pl, bot, maincard);
			while (check)
			{

				cout << "select the taken card\n";
				k= correctinput();
				check = checkCard(maincard, pl.card[k - 1]);
				check = !check;
			}
			
			checkAct=checkActivity(pl, bot, pl.card[k - 1],true); //проверка и выполнение действий карт

			moveCard(maincard, pl.card[k - 1]);
			pl.deletecard( k);
			if (checkAct && pl.qcard != 0) {
				allInfo(pl, bot, maincard);
				Sleep(3000);
				youselect(pl, bot, maincard);
			}
		}
	}
	
	if (check) {
		while (check) // ход картой 
		{
			cout << "select card\n";
			k=correctinput();

			check = checkCard(maincard, pl.card[k - 1]);
			check = !check;
		}

		checkAct=checkActivity(pl, bot, pl.card[k - 1],true); //проверка и выполнение действий карт
		
		moveCard(maincard, pl.card[k - 1]);
		pl.deletecard( k);
		if (checkAct && pl.qcard != 0) {
			allInfo(pl, bot, maincard);
			Sleep(3000);
			game=youselect(pl, bot, maincard);
		}
	}

	if (pl.qcard == 0) {
		game = false;
	}
	return game;
	//конец твойго хода
};

bool botselect(Player& pl, Player& bot, Card& maincard) {
	int i, k,imax=0,costimax;
	string take;
	bool check = false, game = true,checkAct = false;

	// ход компьютера

	for (i = 0; i < bot.qcard; i++) {
		setDefCost(bot.card[i]);
		changeCost(pl, bot, bot.card[i], maincard);
	}

	for (i = 0; i < bot.qcard; i++) {
		if (returnCost(bot.card[i])>0 && returnCost(bot.card[i]) >= returnCost(bot.card[imax])) {
			imax = i;
		}
	}
	costimax = returnCost(bot.card[imax]);

	if (costimax > 0) {
		cout << "bot select card: ";
		Sleep(2500);
		cardOutput(bot.card[imax]);
		Sleep(2500);
		cout << "\n";
		checkAct = checkActivity(pl, bot, bot.card[imax], false); //проверка и выполнение действий карт
		moveCard(maincard, bot.card[imax]);
		bot.deletecard(imax + 1);
		if (checkAct && bot.qcard != 0) {
			allInfo(pl, bot, maincard);
			Sleep(3000);
			game = botselect(pl, bot, maincard);
		}
	}

	if (costimax == -1000) {
		cout << "bot take a card: ";
		Sleep(2000);
		bot.takecard();
		Sleep(2000);
		cardOutput(bot.card[bot.qcard - 1]);
		cout << "\n";
		check = checkCard(maincard, bot.card[bot.qcard - 1]); // проверка может ли бот положить карту, которую взял
		if (check) {
			cout << "bot select the taken card: ";
			Sleep(2000);
			cardOutput(bot.card[bot.qcard - 1]);
			Sleep(2000);
			cout << "\n";
			checkAct = checkActivity(pl, bot, bot.card[bot.qcard - 1],false);
			moveCard(maincard, bot.card[bot.qcard - 1]);
			bot.deletecard( bot.qcard);
			if (checkAct && bot.qcard != 0) {
				allInfo(pl, bot, maincard);
				Sleep(3000);
				game = botselect(pl, bot, maincard);
			}
		}

	}
	if (bot.qcard == 0) {
		//cout << " Bot win!";
		game = false;
	}
	return game;
};

int main() {
	bool game = true;
	bool rmaincard=true;
	srand(time(NULL));
	
	Player pl;
	Player bot;
	pl.set();
	bot.set();
	Card maincard;
	while (rmaincard) {
		randomCard(maincard);
		if (returnColor(maincard) != 0) {
			rmaincard = false;
		}
	}

	while (game)
	{
		if(game){
			allInfo(pl, bot, maincard); // выводит информацию о картах игроков
			game = youselect(pl, bot, maincard);
		} 
		if (game) {
			allInfo(pl, bot, maincard);
			game = botselect(pl, bot, maincard);
			if (!game) { cout << "You lose! Bot win!"; }
		} else{ cout << "You win!"; } 
	}
	return 0;
}