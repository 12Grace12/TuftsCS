#include <iostream>

#include "WordFreqList.h"

void print(WordFreqList list);

using namespace std;

int main()
{
	WordFreqList list = empty();
	WordFreq f;
	f.word = "hello";
	f.freq = 3;
	WordFreq g;
	g.word = "howdy";
	g.freq = 4;
	WordFreq h;
	h.word = "HEYY";
	h.freq = 15;
	list = prepend(f, list);
	list = prepend(g, list);
	insertAfter(h, list);
	print(list);
	return 0;
}

void print(WordFreqList list)
{
    if (isEmpty(list))
	return;
    else {
	cout << first(list).word << endl;
	print(rest(list));
    }
}