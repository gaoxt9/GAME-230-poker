#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <string>

#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif

using namespace std;

struct card
{
	int value;
	string suit;
};

struct node
{
	card poker;
	node* next;
};

struct deck_list
{
	node* head;
};

deck_list* create_deck_list()
{
	deck_list* list = new deck_list;
	list->head = nullptr;
	return list;
}

string wrapValueForCard(int cardValue)
{
	if (cardValue == 11)
	{
		return "J";
	}
	if (cardValue == 12)
	{
		return "Q";
	}
	if (cardValue == 13)
	{
		return "K";
	}
	if (cardValue == 1 || cardValue == 14)
	{
		return "A";
	}
	return to_string(cardValue);
}

void print_deck(deck_list* list)
{
	node* n = list->head;
	while (n != nullptr)
	{
		cout << n->poker.suit << "-" << wrapValueForCard(n->poker.value) << " ";
		n = n->next;
	}
	cout << endl;
}

void add_first(deck_list* list, card newPoker)
{
	node* n = new node;
	n->poker = newPoker;
	n->next = list->head;
	list->head = n;
}

void del_deck_list(deck_list* list)
{
	node* n = list->head;
	while (n != nullptr)
	{
		node* temp = n;
		n = n->next;
		delete temp;
	}

	n = nullptr;
	delete list;
}

int count_deck_cards(deck_list* list)
{
	int count = 0;
	node* n = list->head;
	while (n != NULL)
	{
		++count;
		n = n->next;
	}
	return count;
}

//// crash check
card get_card_from_deck(deck_list* list, int index)
{
	node* n = list->head;
	while (index > 0)
	{
		n = n->next;
		--index;
	}
	return n->poker;
}

void remove_first_card(deck_list* list)
{
	if (list->head == nullptr)
	{
		cout << "Error!" << endl;
		return;
	}

	node* n = list->head;
	list->head = n->next;
	delete n;
}

void remove_card_from_deck(deck_list* list, int index)
{
	if (index == 0)
	{
		remove_first_card(list);
		return;
	}

	node* temp = list->head;
	while (index > 1)
	{
		temp = temp->next;
		--index;
	}

	node* n = temp->next;
	temp->next = n->next;
	delete n;
}

void moneyLeft(int leftMoney)
{
	cout << "You pay a $1 ante and now have $" << leftMoney << endl << endl;
}

void showDeckCardsNumber(int numOfCardsInDeck)
{
	cout << "The deck contains " << numOfCardsInDeck << " cards;" << endl << endl;
}

void showOptions()
{
	cout << "OPTIONS..." << endl;
	cout << "- Type the letters for the cards you wish to keep. (i.e., \"acd\")" << endl;
	cout << "- Type \"deck\" to view the cards remaining in the deck." << endl;
	cout << "- Type \"none\" to discard all cards in your hand." << endl;
	cout << "- Type \"all\" to keep all cards in your hand." << endl;
	cout << "- Type \"exit\" to exit the game." << endl;
	cout << "- Type \"swap\" to CHEAT and swap a card in your hand with one in the deck." << endl;
	cout << "YOUR CHOICE: ";
}

void cardsInHand(card* cardsInHand)
{
	cout << "Your hand contains:" << endl;
	for (int i = 0; i < 5; ++i)
	{
		cout << char('a' + i) << ": " << cardsInHand[i].suit << " " << wrapValueForCard(cardsInHand[i].value) << endl;
	}
	cout << endl;
}

bool checkChoice(string command)
{
	if (command == "")
	{
		return false;
	}

	bool isOption = command == "deck" || command == "none" || command == "all" || command == "exit" || command == "swap";
	if (isOption == true)
	{
		return true;
	}

	string abcde = "abcde";


	if (command.length() > 5)
	{
		return false;
	}

	for (unsigned int i = 0; i < command.length(); ++i)
	{
		if (abcde.find(command[i]) != -1)
		{
			abcde[abcde.find(command[i])] = 0;
		}
		else
		{
			return false;
		}
	}

	return true;
}

string howManyOfAKind(int* arr)
{
	int firstGroup = 0, secondGroup = 0;

	int firstElm = arr[0], secondElm;

	//    for (int j = 0; j < 5; ++j)
	//    {
	//        cout << arr[j] << " ";
	//    }

	for (int i = 1; i < 5; ++i)
	{
		if (firstElm == arr[i])
		{
			firstElm = arr[i];
			firstGroup++;
		}
	}

	for (int j = 1; j < 4; ++j)
	{

		if (arr[j] != firstElm && arr[j] == arr[j + 1])
		{
			secondElm = arr[j];
			secondGroup++;
		}
	}

//out << firstGroup << "   dadsddsda   " << secondGroup << endl;

	if (firstGroup == 3 || secondGroup == 3)
	{
		return "Four of A Kind";
	}
	else if ((firstGroup == 2 && secondGroup == 1) || (firstGroup == 1 && secondGroup == 2))
	{
		return "Full House";
	}
	else if ((firstGroup == 2 && secondGroup ==0) || (firstGroup == 0 && secondGroup == 2))
	{
		return "Three of A Kind";
	}
	else if ((firstGroup == 1 && secondGroup == 1) || (firstGroup == 1 && secondGroup == 1))
	{
		return "Two Pair";
	}
	else if (firstGroup == 1 && secondGroup < 1)
	{
		if (firstElm > 10 || firstElm == 1)
		{
			return "One Pair";
		}
		else
		{
			return "none";
		}

	}
	else if (firstGroup < 1 && secondGroup == 1)
	{
		if (secondElm > 10 || secondElm == 1)
		{
			return "One Pair";
		}
		else
		{
			return "none";
		}

	}
	else
	{
		return "none";
	}
}

int checkGameForMoney(card* matchingCards, int& currentMoney)
{
	int cardsValue[5];
	bool isFlush = true, isConseq = true;

	for (int f = 0; f < 4; ++f)
	{
		if (matchingCards[f].suit != matchingCards[f + 1].suit)
		{
			isFlush = false;
		}
	}

	for (int i = 0; i < 5; ++i)
	{
		cardsValue[i] = matchingCards[i].value;
	}

	sort(cardsValue, cardsValue + 5);

	string thePokerHand = howManyOfAKind(cardsValue);

	// check if they are consequential


	if (cardsValue[0] == 1 || cardsValue[0] == 14)
	{
		if ((cardsValue[1] == 10 && cardsValue[2] == 11 && cardsValue[3] == 12 && cardsValue[4] == 13) ||  (cardsValue[1] == 2 && cardsValue[2] == 3 && cardsValue[3] == 4 && cardsValue[4] == 5))
		{
			isConseq = true;
		}
		else
		{
			isConseq = false;
		}
	}
	else
	{
		for (int t = 0; t < 4; t++)
		{
			if (cardsValue[t] + 1 != cardsValue[t + 1])
			{
				isConseq = false;
			}
		}
	}


	if (cardsValue[0] == 1 && cardsValue[1] == 10 && isFlush)
	{
		currentMoney += 800;
		cout << "Royal Flush" << endl; // 800
		cout << "You earned $800" << endl;
	}
	else if (isFlush && isConseq)
	{
		currentMoney += 50;
		cout << "Straight Flush" << endl;  //50
		cout << "You earned $50" << endl;
	}
	else if (thePokerHand == "Four of A Kind")
	{
		currentMoney += 25;
		cout << thePokerHand << endl; // 25
		cout << "You earned $25" << endl;
	}
	else if (thePokerHand == "Full House")
	{
		currentMoney += 9;
		cout << thePokerHand << endl; // 9
		cout << "You earned $9" << endl;
	}
	else if (isFlush)
	{
		currentMoney += 6;
		cout << "Flush" << endl; // 6
		cout << "You earned $6" << endl;
	}
	else if (isConseq)
	{
		currentMoney += 4;
		cout << "Straight" << endl; // 4
		cout << "You earned $4" << endl;
	}
	else if (thePokerHand == "Three of A Kind")
	{
		currentMoney += 3;
		cout << thePokerHand << endl; // 3
		cout << "You earned $3" << endl;
	}
	else if (thePokerHand == "Two Pair")
	{
		currentMoney += 2;
		cout << thePokerHand << endl; // 2
		cout << "You earned $2" << endl;
	}
	else if (thePokerHand == "One Pair")
	{
		currentMoney += 1;
		cout << thePokerHand << endl; // 1
		cout << "You earned $1" << endl;
	}
	else
	{
		cout << "No poker hand scored";
	}


	cout << endl;
	return 0;
}

bool isCardInDeck(deck_list* existList, int selectedCardValue, string selectedCardSuit)
{
	int listSize = count_deck_cards(existList);
	card tempCard;

	for (int i = 0; i < listSize; ++i)
	{
		tempCard = get_card_from_deck(existList, i);

		if (selectedCardValue == tempCard.value && selectedCardSuit == tempCard.suit)
		{
			return true;
		}
	}

	return false;
}


void swap(deck_list* list, card* playerCards)
{
	char cardInHand;
	int inputValue;
	char inputSuit;
	string graphicSuit;
	card selectedCard, matchedCard, tempCard;
	int selectedLetter;
	int listLength = count_deck_cards(list);

	cout << "Enter the letter of the card in hand: ";

	cin >> cardInHand;

	while (cardInHand >= 'a' + 5 || cardInHand < 'a')
	{
		cout << "Input invalid, please re-enter" << endl;
		cin.clear();
		cin.ignore(80, '\n');
		cin >> cardInHand;
	}


	selectedLetter = int(cardInHand) - 97;
	selectedCard = playerCards[selectedLetter];

	cout << "Enter the value of the card in the deck to swap: ";
	cin >> inputValue;

	if (inputValue == 14)
	{
		inputValue = 1;
	}


	cout << "Enter the suit (c, d, h, s) of the card in the deck to swap with: ";
	cin >> inputSuit;

	switch (inputSuit)
	{
		case 's':
			graphicSuit = "spade";
			break;
		case 'h':
			graphicSuit = "heart";
			break;
		case 'd':
			graphicSuit = "diamond";
			break;
		case 'c':
			graphicSuit = "club";
	}

	while (isCardInDeck(list, inputValue, graphicSuit) == false)
	{
		cin.clear();
		cin.ignore(80, '\n');

		cout << "Card is not in deck, please re-enter" << endl;

		cout << "Enter the value of the card in the deck to swap: " << endl;
		cin >> inputValue;

		if (inputValue == 14)
		{
			inputValue = 1;
		}	

		cout << "Enter the suit (c, d, h, s) of the card in the deck to swap with: " << endl;
		cin >> inputSuit;

		switch (inputSuit)
		{
		case 's':
			graphicSuit = "spade";
			break;
		case 'h':
			graphicSuit = "heart";
			break;
		case 'd':
			graphicSuit = "diamond";
			break;
		case 'c':
			graphicSuit = "club";
		}

	}

	for (int deckIndex = 0; deckIndex < listLength; ++deckIndex)
	{
		matchedCard = get_card_from_deck(list, deckIndex);
		if (inputValue == matchedCard.value && graphicSuit == matchedCard.suit)
		{
			// found the matched card
			tempCard = selectedCard; // card in user hand
			playerCards[selectedLetter] = matchedCard;
			remove_card_from_deck(list, deckIndex);
			add_first(list, tempCard);
			break;
		}
	}
}

deck_list* initDeck(deck_list* initList)
{
	card aaa;

	for (int i = 1; i < 5; i++)
	{
		string thisSuit = "";
		switch (i)
		{
		case 1:
			thisSuit = "spade";
			break;
		case 2:
			thisSuit = "heart";
			break;
		case 3:
			thisSuit = "diamond";
			break;
		case 4:
			thisSuit = "club";
		}

		for (int j = 1; j <= 13; j++)
		{
			aaa.suit = thisSuit;
			aaa.value = j;
			add_first(initList, aaa);
		}
	}
	return initList;
}


void refillDeck(deck_list* listToBeRefilled, card* existCards)
{
	cout << "Deck gets refilled" << endl << endl;

	int delTimes = count_deck_cards(listToBeRefilled);
	card tempCard;
	// clear deck
	for (int i = 0; i < delTimes; ++i)
	{
		remove_first_card(listToBeRefilled);
	}

	initDeck(listToBeRefilled);

	for (int j = 0; j < 5; ++j)
	{
		for (int deckIndex = 0; deckIndex < count_deck_cards(listToBeRefilled); ++deckIndex)
		{
			tempCard = get_card_from_deck(listToBeRefilled, deckIndex);
			if (existCards[j].value == tempCard.value && existCards[j].suit == tempCard.suit)
			{
				remove_card_from_deck(listToBeRefilled, deckIndex);
			}
		}
	}
}

void assignCardsToPlayer(deck_list* list, string newCards, card* playerCards)
{
	// newCards.length() > count, refill
	if ((int)newCards.length() > count_deck_cards(list))
	{
		refillDeck(list, playerCards);
	}

	int randomCardIndex, index;
	srand((unsigned)time(NULL));

	for (unsigned int i = 0; i < newCards.length(); ++i)
	{
		randomCardIndex = rand() % count_deck_cards(list);
		index = static_cast<int>(newCards[i]) - 97;
		playerCards[index] = get_card_from_deck(list, randomCardIndex);
		remove_card_from_deck(list, randomCardIndex);
	}
}

string filterCardsToKeep(string oldCards)
{
	string allCards = "abcde";
	string cardToKeep = "";

	for (unsigned int i = 0; i < allCards.length(); ++i)
	{
		if (oldCards.find(allCards[i]) == -1)
		{
			cardToKeep += allCards[i];
		}
	}

	return cardToKeep;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
		_CRTDBG_LEAK_CHECK_DF);

	int money = 10;
	card playerCards[5];

	deck_list* list = create_deck_list();

	initDeck(list);

	cout << "Welcome to Video Poker!" << endl;
	cout << "You have started with $10" << endl;

	while (money > 0)
	{
		money--;

		string inputChoice = "";

		moneyLeft(money);

		// give player all five cards
		assignCardsToPlayer(list, "abcde", playerCards);

		cardsInHand(playerCards);

		showDeckCardsNumber(count_deck_cards(list));

		while (checkChoice(inputChoice) == false || inputChoice == "swap" || inputChoice == "deck")
		{
			showOptions();

			if (inputChoice != "")
			{
				cin.clear();
				cin.ignore(1000, '\n');
			}

			cin >> inputChoice;

			if (inputChoice == "deck")
			{
				print_deck(list);
			}
			else if (inputChoice == "none")
			{
				assignCardsToPlayer(list, "abcde", playerCards);
				cardsInHand(playerCards);
				checkGameForMoney(playerCards, money);
				break;
			}
			else if (inputChoice == "all")
			{
				cardsInHand(playerCards);
				checkGameForMoney(playerCards, money);
				break;
			}
			else if (inputChoice == "exit")
			{
				del_deck_list(list);
				list = nullptr;
				return 0;
			}
			else if (inputChoice == "swap")
			{
				swap(list, playerCards);
				cout << "new cards in hand are: " << endl;
				cardsInHand(playerCards);
			}
			else
			{
				if (checkChoice(inputChoice))
				{
					assignCardsToPlayer(list, filterCardsToKeep(inputChoice), playerCards);
					cardsInHand(playerCards);
					checkGameForMoney(playerCards, money);
					break;
				}
				else
				{
					cout << "Invalid, please re-enter" << endl << endl;
				}
			}
		}

		cout << "You now have $" << money << endl;
	}

	del_deck_list(list);
	list = nullptr;

	cout << "-------------------------------------------------" << endl << endl;
	cout << "You are out of money! Game Over!" << endl;

	return 0;
}