
#include <ncurses.h>
#include <unistd.h>
#include <sstream>
#include <string>

using namespace std;

template<class T>
std::string convertToString(T data) {
	ostringstream stream;
	stream << data;
	return stream.str();
}

std::string buffer;

static int t = 1;

void printWord(WINDOW* win, char wordBuffer[]) {
	if (++t > 3) {
		t = 1;
	}

	wattrset(win, COLOR_PAIR(t));
	wprintw(win, wordBuffer);
}

void printColoredText(WINDOW *win, std::string text) {


    char wordBuffer[100] = "heeej!"; //100 is the longest word
    int index = 0;
    for (auto c: text) {
    	wordBuffer[index] = c;
    	++index;

    	if (c == ' ' or c == 0) {
    		wordBuffer[index] = 0; //terminate string
    		index = 0;
			printWord(win, wordBuffer);
    	}
    }
    wordBuffer[index] = 0;
    printWord(win, wordBuffer);
}

int main() {
	initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	bkgd(COLOR_PAIR(1));

	printw("hej jag testar");
	refresh();

	WINDOW *win = stdscr;

	while (1) {
		t = 0;
		int key = getch();
		clear();
		move(0,0);
		printColoredText(win, "\tmatedit - titel.txt");
		move(10, 10);
		wprintw(win, convertToString(key).c_str());

		if (key == 127) {
			if (buffer.size()) {
				buffer.resize(buffer.size() -1);
			}
		}
		else {
			buffer += (char) key;
		}
		wmove (win, 1, 0);
//		wprintw(win, buffer.c_str());
		printColoredText(win, buffer.c_str());
	}

	endwin();
}
