#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "poker.h"

/* Global instances of the two players */
struct player P1, P2;

	/* Parse card from a 2 char input */
	struct card parse(const char *card)
	{
		/* TASK 14: parse input and store in card data structure. */
		struct card c;
		/* Hint: You could use switch statements here */
		
		switch(*card)	
		{
			case '2':
				c.val = c2;
				break;
			case '3':
				c.val = c3;
				break;	
			case '4':
				c.val = c4;
				break;
			case '5':
				c.val = c5;
				break;	
			case '6':
				c.val = c6;
				break;
			case '7':
				c.val = c7;
				break;	
			case '8':
				c.val = c8;
				break;
			case '9':
				c.val = c9;
				break;	
			case 'T':
				c.val = c10;
				break;
			case 'J':
				c.val = cJ;
				break;	
			case 'Q':
				c.val = cQ;
				break;
			case 'K':
				c.val = cK;
				break;	
			case 'A':
				c.val = cA;
				break;		

		}
		card++;
		switch(*card)
		{
			case 'H':
				c.suit = H;
				break;
			case 'D':
				c.suit = D;
				break;
			case 'S':
				c.suit = S;
				break;
			case 'C':
				c.suit = C;
				break;

		}







		return c;
	}

	/* Count the number of occurrences of each card 2 through Ace */
	void count_cards(struct player *p)
	{
		/* TASK 13:  
		 * Iterate through the cards and increment the counter for each card
		 */
		int i;
		for(i = 0; i < 5; i++)
		{
			if((*p).cards[i].val == 2)
			{
				(*p).card_count[0]++;
			}
			if((*p).cards[i].val == 3)
			{
				(*p).card_count[1]++;
			}
			if((*p).cards[i].val == 4)
			{
				(*p).card_count[2]++;
			}
			if((*p).cards[i].val == 5)
			{
				(*p).card_count[3]++;
			}
			if((*p).cards[i].val == 6)
			{
				(*p).card_count[4]++;
			}
			if((*p).cards[i].val == 7)
			{
				(*p).card_count[5]++;
			}
			if((*p).cards[i].val == 8)
			{
				(*p).card_count[6]++;
			}
			if((*p).cards[i].val == 9)
			{
				(*p).card_count[7]++;
			}
			if((*p).cards[i].val == 10)
			{
				(*p).card_count[8]++;
			}
			if((*p).cards[i].val == 'J')
			{
				(*p).card_count[9]++;
			}
			if((*p).cards[i].val == 'Q')
			{
				(*p).card_count[10]++;
			}
			if((*p).cards[i].val == 'K')
			{
				(*p).card_count[11]++;
			}
			if((*p).cards[i].val == 'A')
			{
				(*p).card_count[12]++;
			}
			
		}

	}	

	int is_flush(struct player *p)
	{
		/* TASK 12:
		 * Hand is flush if suit of all the cards is the same
		 */
		int s = (*p).cards[0].suit;
		if(((*p).cards[1].suit == s) && ((*p).cards[2].suit == s) && ((*p).cards[3].suit == s) && ((*p).cards[4].suit == s))
		{
			return 1;
		}
		return 0; /* Return 1 if flush */
	}
	
	int is_fullhouse(struct player *p)
	{
		bool triple = false;
		bool pair = false;
		int i;
		for(i = 0; i < 13;i++)
		{	
			if((*p).card_count[i] == 3)
				triple = true;
			else if((*p).card_count[i] == 2)
				pair = true;
		}

		if(triple && pair)
			return 1;
		else
			return 0;
	}	

	int is_straight(struct player *p)
	{
		/* NOTE: By this stage, the vector must be constructed.
		 * 
		 * The hand is a straight, if the cards are sequential.
		 * A2345 as well as TJQKA are both valid straights, and Ace 
		 * assumes the value of 1 or 13, but not both.
		 */

		/* TASK 11: Check for regular straights
 		 * Hint: If this is a straight, player's card_count for i, i+1, i+2, i+3 and i+4 should be 1. */
		int i;
		for(i = 0; i < 9;i++)
		{
			if(((*p).card_count[i] == 1) && ((*p).card_count[i + 1] == 1) && ((*p).card_count[i + 2] == 1) && ((*p).card_count[i + 3] == 1) && ((*p).card_count[i + 4] == 1))
			{
				return 1;
			}
		}

		/* Check for A2345
		 * TASK 10: If the hand is A2345, reset the bit for highcard Ace in the player's vector to appropriately reflect that the value of A is not 13. 
		 * Hint: 1 << position will generate a bit mask for the position of Ace. Xoring it with the vector will reset the bit.
		 */
		if(((*p).card_count[0] == 1) && ((*p).card_count[1] == 1) && ((*p).card_count[2] == 1) && ((*p).card_count[3] == 1) && ((*p).card_count[12] == 1))
		{
			(*p).vector^= 1 << 12;
			return 1; 

		}
		return 0; /* Return 1 if straight */	
	}

	int is_straight_flush(struct player *p)
	{
		/* TASK 9: Detect straight flush. A straight flush is nothing but a straight and a flush */
		if((is_straight(p) == 1) && (is_flush(p) == 1))
		{
			return 1;
		}
		else
			return 0; /* Return 1 if straight flush */
	}
			
	/* This is the main function that converts the player's hand into weighted unsigned long number. 
	It is a 55bit vector as shown below (2 is the LSB and StraightFlush is the MSB) */
	/* 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A, 22, 33, 44, 55, 66, 77, 88, 99, TT, JJ, QQ, KK, AA,
	222, 333, 444, 555, 666, 777, 888, 999, TTT, JJJ, QQQ, KKK, AAA, Straight, Flush,Full House, 2222, 3333, 
	4444, 5555, 6666, 7777, 8888, 9999, TTTT, JJJJ, QQQQ, KKKK, AAAA, StraightFlush */
	/* The number of occurrences of each number in the hand is first calculated in count_cards. 
	Then, depending on the numeber of occurrences, the corresponding bit in the bit-vector is set. 
	In order to find the winner, a simple comparison of the bit vectors (i.e., unsigned long integers) will suffice! */
	void eval_strength(struct player *p)
	{
		unsigned int straight_or_flush_possible;
		unsigned int i;
		straight_or_flush_possible = 1; 
	
		/*
		 * TASK 6: Invoke the function to count the occurrences of each card
		 */
		count_cards(p);		
		/*
		 * TASK 7: Iterate through the card_count array, and set the appropriate bit in the bit vector.
		 * For example, if the hand is JH JS 3C AH 4H, set the 23rd bit to indicate a pair of jacks, and 2nd, 3rd and 13th bit to indicate 3, 4 and A respectively. */

		for(i = 0; i < 13; i++)
		{
			switch((*p).card_count[i])
			{
				case 1: (*p).vector |= 1UL << (i);
				case 2: (*p).vector |= 1UL << (13 + i);
				case 3: (*p).vector |= 1UL << (26 + i); 
				case 4: (*p).vector |= 1UL << (42 + i);
			}

		}


		/* TASK 8:
		 * Check if this is a straight, flush or a straight flush, and set the appropriate bit in the vector.
		 */
		if(is_straight(p) == 1)
		{
			(*p).vector |= 1UL << 39;
		}
		if(is_flush(p) == 1)
		{
			(*p).vector |= 1UL << 40;
		}
		if(is_straight_flush(p) == 1)
		{
			(*p).vector |= 1UL << 55;
		}
		if(is_fullhouse(p) == 1)
		{
			(*p).vector |= 1UL << 41;
		}

}

	/* Parse each hand in the input file, evaluate the strengths of hands and identify a winner by comparing the weighted vectors */
	void compare_hands(FILE *fp)
	{
		char p1[5][3];
		char p2[5][3];
		int i;
	
		while(fscanf(fp, "%s %s %s %s %s %s %s %s %s %s", 
			&p1[0][0], &p1[1][0], &p1[2][0], &p1[3][0], &p1[4][0], 
			&p2[0][0], &p2[1][0], &p2[2][0], &p2[3][0], &p2[4][0]) == 10) {
			memset(&P1, 0, sizeof(struct player));
			memset(&P2, 0, sizeof(struct player));
			for(i = 0; i < 5; i++) {
				P1.cards[i] = parse(&p1[i][0]);
				P2.cards[i] = parse(&p2[i][0]);
			}
			
			/* TASK 4: Invoke eval_strength for each player */

			eval_strength(&P1);
			eval_strength(&P2);		

			/* TASK 5: Report the winner (e.g., "Player 1 wins") depending on whoever has the higher vector */
			FILE *f;
			f = fopen("Output.txt", "a");
			if(P1.vector > P2.vector)
			{
				fprintf(f, "Player 1 wins\n");		
			}
			else if(P1.vector < P2.vector)
			{
				fprintf(f, "Player 2 wins\n");
			}
		}
		fclose(fp);
	}
	
	int main(int argc, char *argv[])
	{
		FILE *fp;
	
		/* TASK 2: Validate command line arguments and try to open the file. Exit on failure. */
		fp = fopen(argv[1],"r");
		if(fp == 0)
		{
			printf("File not present. Exiting now...");
			return 0;
		}
		/* TASK 3: Invoke the compare hands function */
		
		compare_hands(fp);
	
		return 0;
	}
		
