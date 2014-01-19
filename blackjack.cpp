#include <iostream>
#include <vector>
#include <string>

using namespace std;

const char * cardValues[] = {"ACE", "TWO", "THREE", "FOUR", "FIVE", "SIX", 
								"SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING"};

const char * suitNames[] = {"Hearts", "Spades", "Clubs", "Diamonds"};

struct card{
	int number;
	int suit;
};

class deck{
private:	
	vector<card*> *mycards;
	vector<card*> *holderdeck;
	int currIndex;
	void shuffle(){
		int count = 0;

		for(int i=0; i< (mycards->size())/2; i++, count++){
			holderdeck->at(count) = (mycards->at(26+i));
			count++;
			holderdeck->at(count) = (mycards->at(i));
		}
		*mycards = *holderdeck;
		
	}
public:
	deck(){
		currIndex = 0;
		holderdeck =  new vector<card*>;
		holderdeck->resize(52);
		mycards = new vector<card*>;
		for(int i = 0; i<4; i++){
			for(int j=0;j<13; j++){
				card *newCard = new card;
				newCard->number = j;
				newCard->suit = i;
				mycards->push_back(newCard);
			}
		}
		for(int j=0; j<8; j++){
			shuffle();
			//cout << " Size " << mycards->size() << endl;
		}

	}
	card* dealCard(){
		currIndex++;
		if(currIndex >=52){
			currIndex = 0;
			for(int j=0; j<4; j++){
				shuffle();
			}
		}
		return mycards->at(currIndex-1);
	}
	~deck(){
		while(mycards->size() !=0 ){
			cout << ".";
			card *newCard;
			newCard = mycards->back();
			mycards->pop_back();
			delete newCard;
		}
		cout << endl;
		//delete holderdeck;
	}
	void printCard(card *c){
		cout << "[" << cardValues[c->number] << " of " << suitNames[c->suit] << "]   "  ;
	}
	void printDeck(){
		for(int i = 0; i < mycards->size(); i++){
			cout << "[" << cardValues[mycards->at(i)->number] << " of " << suitNames[mycards->at(i)->suit] << "]   "  ;
		}
		
	}

};
class game{
private:
	deck *gameDeck;
	int sumValue(vector<card*> *hand){
		int totalvalue = 0;
		for(int i=0; i<hand->size(); i++){
			if((hand->at(i)->number)>0 && (hand->at(i)->number)<10){
				totalvalue += (1+hand->at(i)->number);
			}else if ((hand->at(i)->number) == 0){
				totalvalue += (11);
			}else{
				totalvalue += 10;
			}
			//cout << "Total value = " << totalvalue << endl;
		}
		return totalvalue;
	}
	void printHand(vector<card*> *hand){
		for(int i=0; i<hand->size(); i++){
			gameDeck->printCard(hand->at(i));
			cout << "  ";
		}
	}
	int hand(){
		card *p1, *p2, *d1, *d2;
		vector<card*> *myhand = new vector<card*>(0);
		vector<card*> *dealerhand = new vector<card*>(0);
		myhand->push_back(gameDeck->dealCard());
		dealerhand->push_back(gameDeck->dealCard());
		myhand->push_back(gameDeck->dealCard());
		dealerhand->push_back(gameDeck->dealCard());

		cout << "Hand size " << myhand->size();
		cout << endl<< "Your hand :   " ;
		printHand(myhand);
		cout << endl << "Dealer hand : ";
		gameDeck->printCard(dealerhand->at(0)); 
		cout << "    [ X X X ]" << endl;
		string action;
		bool keepgoing = true;
		int handVal = sumValue(myhand), dealVal = sumValue(dealerhand);
		while(keepgoing){
			cout << "What would you like to do? (hit, stand) " << endl;

			cin >> action;
			if(action == "hit"){
				myhand->push_back(gameDeck->dealCard());
				handVal = sumValue(myhand);
				cout << "Your Hand : ";
				printHand(myhand);

				if(handVal > 21){
					cout << "\nDealer hand : " ;
					printHand(dealerhand);
					cout << "\nBust! Dealer wins!";
					keepgoing = false;
				}
				
			}else if (action == "stand"){
				cout << " \nDealer hand : ";  printHand(dealerhand);
				while(dealVal < 17){
					cout << " \nDealer hits : ";
					card *newCard = gameDeck->dealCard();
					gameDeck->printCard(newCard);
					dealerhand->push_back(newCard);
					dealVal = sumValue(dealerhand);
					
				}
				cout << "\nYour Hand : "; printHand(myhand);
				cout << " \nDealer hand : ";  printHand(dealerhand);
				cout << "\nMy hand value " << handVal << "\nDealer hand value " << dealVal << endl;

				if(dealVal > 21){
						cout << " Dealer busts! You win! ";
				}else if(handVal > dealVal){
					cout << "You win! ";
				}else if(handVal <= dealVal){
					cout << "Dealer wins ";
				}
				keepgoing = false;
			}else{
				cout << "I didn't recognize that input. Please try again. ";
			}
		}	
		delete myhand;
		delete dealerhand;
		return 0;
	}
public:
	game(){
		gameDeck = new deck();

		cout << "The value is "  << endl;
		cout << "As an enum it's " << cardValues[10] << endl;
		gameDeck->printDeck();

	}
	void play(){
		cout << "\n\nLet's start a new game " << endl;
		bool gamePlay = true;
		while(gamePlay){
			int playval = hand();
			char c;
			cout << "Deal again? (y/n)" << endl;
			cin >> c;
			if(c=='n'){ gamePlay = false; }
			
		}
		cout << endl;
	}
	~game(){
		delete gameDeck;
	}
};
int main(int argc, const char * argv){
	cout << "Welcome to Blackjack!\n";
	game *myGame = new game();
	myGame->play();
	delete myGame;
	
}


