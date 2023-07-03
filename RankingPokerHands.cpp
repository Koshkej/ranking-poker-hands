#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;

class handserialized {

public:

	int hand[5][2];
	int combination = 0;

	std::vector<int> comba, anoth; // for solution when tie by combination-types

	handserialized(std::string strhand) {

		combination = 0;
		std::vector<std::string> buffercard;

		for (int i = 0; i < strhand.size(); i++) {
			if (strhand[i] == ' ') {
				strhand.erase(i, 1);
			}
			else {
				std::string buffer;
				buffer.push_back(strhand[i]);
				buffer.push_back(strhand[i+1]);
				buffercard.push_back(buffer);
				strhand.erase(i, 2);
			}
			i = 0;
		}

		for (int i = 0; i < 5; i++) {
			switch (buffercard[i][0])
			{
			case '2':
				hand[i][0] = 2;
				break;
			case '3':
				hand[i][0] = 3;
				break;
			case '4':
				hand[i][0] = 4;
				break;
			case '5':
				hand[i][0] = 5;
				break;
			case '6':
				hand[i][0] = 6;
				break;
			case '7':
				hand[i][0] = 7;
				break;
			case '8':
				hand[i][0] = 8;
				break;
			case '9':
				hand[i][0] = 9;
				break;
			case 'T':
				hand[i][0] = 10;
				break;
			case 'J':
				hand[i][0] = 11;
				break;
			case 'Q':
				hand[i][0] = 12;
				break;
			case 'K':
				hand[i][0] = 13;
				break;
			case 'A':
				hand[i][0] = 14;
				break;
			}
		}

		for (int i = 0; i < 5; i++) {
			switch (buffercard[i][1])
			{
				case 'S':
					hand[i][1] = 0;
					break;
				case 'H':
					hand[i][1] = 1;
					break;
				case 'D':
					hand[i][1] = 2;
					break;
				case 'C':
					hand[i][1] = 3;
					break;
			}
		}

		for (int i = 0; i < 5; i++) {
			int key[2] = { hand[i][0], hand[i][1] };
			int x = i - 1;
			while (x >= 0 && key[0] < hand[x][0]) {
				hand[x + 1][0] = hand[x][0];
				hand[x + 1][1] = hand[x][1];
				x -= 1;
			}
			hand[x + 1][0] = key[0];
			hand[x + 1][1] = key[1];
		}
			
	}

};

int getwin(std::string handA, std::string handB);

void isKindFlushOrStraight(class handserialized &currentHand);
void isKindLineRangs(class handserialized &currentHand);
int  tieCompare(class handserialized &combinationA, class handserialized &combinationB);


int main() {

	std::cout << std::endl << getwin("JC 6H JS JD JH", "JC 7H JS JD JH");

	return 0;

}

int getwin(std::string handA, std::string handB) {

	handserialized serhandA(handA), serhandB(handB);
	
	isKindFlushOrStraight(serhandA);
	isKindLineRangs(serhandA);

	isKindFlushOrStraight(serhandB);
	isKindLineRangs(serhandB);

	/* Compare */

	std::cout << "RES " << serhandA.combination << " " << serhandB.combination << std::endl;

	for (int i = 0; i < 5; i++) {
		std::cout << serhandA.hand[i][0] << " ";
	}
	int bufA = 0;
	for (int i = 0; i < 5; i++) {
		bufA += serhandA.hand[i][0];
	}
	std::cout << " = " << bufA;
	std::cout << std::endl;
	for (int i = 0; i < 5; i++) {
		std::cout << serhandB.hand[i][0] << " ";
	}
	int bufB = 0;
	for (int i = 0; i < 5; i++) {
		bufB += serhandB.hand[i][0];
	}
	std::cout << " = " << bufB;

	if (serhandA.combination > serhandB.combination) return 1;
	else if (serhandA.combination < serhandB.combination) return 2;
	else if (serhandA.combination == serhandB.combination) return tieCompare(serhandA, serhandB);

	return 0;

}

void isKindFlushOrStraight(class handserialized &currentHand) {

	bool localcombination[2] = { false, false }; // Flush, Straight

	/* Flush */

	for (int i = 1; i < 5; i++) {
		if (currentHand.hand[i][1] != currentHand.hand[i - 1][1]) break;
		if (i == 4) localcombination[0] = true;
	}

	/* Straight */

	for (int i = 1; i < 5; i++) {
		if (currentHand.hand[i][0] - currentHand.hand[i - 1][0] != 1) break;
		if (i == 4) localcombination[1] = true;
	}
	
	/* Low-ace straight */

	int bufnum[5];

	for (int i = 0; i < 5; i++) 
		if (currentHand.hand[i][0] == 14) bufnum[i] = 1;
		else bufnum[i] = currentHand.hand[i][0];

	for (int i = 0; i < 5; i++) {
		int key = bufnum[i];
		int x = i - 1;
		while (x >= 0 && key < bufnum[x]) {
			bufnum[x+1] = bufnum[x];
			x -= 1;
		}
		bufnum[x + 1] = key;
	}

	for (int i = 1; i < 5; i++) {
		if (bufnum[i] - bufnum[i - 1] != 1) break;
		if (i == 4) localcombination[1] = true;
	}

	// check combination

	if (localcombination[0] == true && localcombination[1] == true) currentHand.combination = 8;   // Straight flush
	else if (localcombination[0] == true) currentHand.combination = 5;                             // Flush
	else if (localcombination[1] == true) currentHand.combination = 4;                             // Straight

	std::cout << std::endl << currentHand.combination << " -- " << std::endl;

	for (int i = 0; i < 5; i++) {
		currentHand.comba.push_back(currentHand.hand[i][0]);
		currentHand.anoth.push_back(currentHand.hand[i][0]);
	}

	return;

}

void isKindLineRangs(class handserialized &currentHand) {

	bool localcombination[4] = { false, false, false, false }; // Set, 4Kind, OnePair, TwoPair

	/* Set, 4Kind */

	if (currentHand.combination < 7) {

		int bufn = 0;

		for (int i = 1; i < 5; i++) {

			if (currentHand.hand[i][0] == currentHand.hand[i - 1][0]) bufn += 1;
			else if (currentHand.hand[i][0] != currentHand.hand[i - 1][0]) bufn = 0;

			if (bufn == 3) {

				cout << "DESDF";

				localcombination[1] = true;
				currentHand.comba.push_back(currentHand.hand[i][0]);
				
				if (i == 4) {
					currentHand.anoth.clear();
					currentHand.anoth.push_back(currentHand.hand[0][0]);
				}
				else if (i == 3) {
					currentHand.anoth.clear();
					currentHand.anoth.push_back(currentHand.hand[4][0]);
				}

			}
			else if (bufn == 2) {
				localcombination[0] = true;

				currentHand.comba.clear();
				currentHand.anoth.clear();

				currentHand.comba.push_back(currentHand.hand[i][0]);
				currentHand.comba.push_back(currentHand.hand[i - 1][0]);
				currentHand.comba.push_back(currentHand.hand[i - 2][0]);

				if (i == 3) {
					currentHand.anoth.push_back(currentHand.hand[0][0]);
					currentHand.anoth.push_back(currentHand.hand[4][0]);
				}
				else if (i == 2) {
					currentHand.anoth.push_back(currentHand.hand[3][0]);
					currentHand.anoth.push_back(currentHand.hand[4][0]);
				}
				else if (i == 4) {
					currentHand.anoth.push_back(currentHand.hand[0][0]);
					currentHand.anoth.push_back(currentHand.hand[1][0]);
				}

			}

		}

		if (localcombination[1] == true) {
			currentHand.combination = 7; // 4Kind
			return;
		}

	}
	else {
		return;
	}

	std::cout << currentHand.comba[0];


	/* OnePair, TwoPair */

	std::vector<int> lineShort;

	int numone, numtwo;

	for (int i = 1; i < 5; i++) {

		if (localcombination[2] == true && (i > 1 ? currentHand.hand[i][0] != currentHand.hand[i - 2][0] : true) && currentHand.hand[i][0] == currentHand.hand[i - 1][0] && currentHand.hand[i][0] != currentHand.hand[i + 1][0]) {
			
			localcombination[3] = true;

			currentHand.comba.push_back(currentHand.hand[i][0]);
			currentHand.comba.push_back(currentHand.hand[i - 1][0]);

			numtwo = i - 1;

		} 
			
		
		if (localcombination[2] == false && (i > 1 ? currentHand.hand[i][0] != currentHand.hand[i - 2][0] : true) && currentHand.hand[i][0] == currentHand.hand[i - 1][0] && currentHand.hand[i][0] != currentHand.hand[i + 1][0]) {
			localcombination[2] = true;
			if (localcombination[0] != true) {

				currentHand.comba.clear();
				currentHand.anoth.clear();

				currentHand.comba.push_back(currentHand.hand[i][0]);
				currentHand.comba.push_back(currentHand.hand[i - 1][0]);

				numone = i - 1;

			}
		}
			
		
	}

	if (localcombination[0] == true && localcombination[2] == true && currentHand.combination < 6) currentHand.combination = 6;      // Full house
	else if (localcombination[0] == true && localcombination[2] != true && currentHand.combination < 3) currentHand.combination = 3; // Set
	else if (localcombination[2] == true && localcombination[3] == true && currentHand.combination < 2) currentHand.combination = 2; // Two pair
	else if (localcombination[2] == true && localcombination[3] != true && currentHand.combination < 1) currentHand.combination = 1; // One pair

	if (currentHand.combination == 1) for (int i = 0; i < 5; i++) if (i < numone || i > numone + 1) currentHand.anoth.push_back(currentHand.hand[i][0]);

	if (currentHand.combination == 2) for (int i = 0; i < 5; i++) if (i < numone || (i > numone + 1 && i < numtwo) || i > numtwo + 1) currentHand.anoth.push_back(currentHand.hand[i][0]);

	if (currentHand.combination == 4 && currentHand.comba[4] == 14) {
		
		currentHand.comba[4] = 1;

		for (int i = 0; i < 5; i++) {
			int key = currentHand.comba[i];
			int x = i - 1;
			while (x >= 0 && key < currentHand.comba[x]) {
				currentHand.comba[x + 1] = currentHand.comba[x];
				x -= 1;
			}
			currentHand.comba[x + 1] = key;
		}

	}

	return;

}

int tieCompare(class handserialized &combinationA, class handserialized &combinationB) {

	int maxA = 0, maxB = 0;

	for (int i = 0; i < combinationA.comba.size(); i++) {
		if (maxA < combinationA.comba[i]) maxA = combinationA.comba[i];
		if (maxB < combinationB.comba[i]) maxB = combinationB.comba[i];
	}

	int bufsise = combinationA.anoth.size();

	if (maxA == maxB) {
		for (int i = bufsise - 1; i >= 0 ; i--) {
			maxA = combinationA.anoth[i];
			maxB = combinationB.anoth[i];
			cout << maxA << " " << maxB << endl;
			if (maxA != maxB) break;
		}
	}

	if (maxA > maxB) return 1;
	else if (maxA < maxB) return 2;
	else if (maxA == maxB) return 0;

}

/*


TOP

8 (!) Straight flush - 5 êàðò ïîñëåäîâàòåëüíîãî ðàíãà îäíîé ìàñòè
7 (!) Four of a kind - 4 êàðòû îäíîãî ðàíãà 
6 (!) Full house - 2 êàðòû îäíîãî ðàíãà 3 êàðòû îäíîãî ðàíãà
5 (!) Flush - 5 êàðò îäíîé ìàñòè
4 (!) Straight - 5 êàðò ïîñëåäîâàòåëüíûõ ðàíãîâ
3 (!) Set - 3 êàðòû îäíîãî ðàíãà
2 (!) Two pair - 2 êàðòû îäíîãî ðàíãà 2 êàðòû îäíîãî ðàíãà 
1 (!) One pair - 2 êàðòû îäíîãî ðàíãà 
0 High card

T(en), J(ack), Q(ueen), K(ing), A(ce)

S(pades), H(earts), D(iamonds), C(lubs)
*/
