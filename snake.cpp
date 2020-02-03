#include <iostream>
#include <ctime>
#include <ncurses.h>
#include <unistd.h>

using namespace std;
const int width = 40;
const int height = 40;
bool over = false;

enum eDir {UP, DOWN, LEFT, RIGHT};


class cSnake {
private:
	
	int headX;
	int headY;
	eDir direction;
	int tailLength;
	int tailX[200];
	int tailY[200];

public:

	cSnake() {
		headX = width/2;
		headY = height/2;
		direction = UP;
		tailLength = 0;
	}

	void increaseLength() {
		tailLength++;
	}

	void changeDirection(eDir dir) {
		direction = dir;
	}

	void move() {

		int prevX = tailX[0];
		int prevY = tailY[0];
		tailX[0] = headX;
		tailY[0] = headY;
		int prevX2, prevY2;
		for(int i = 1; i < tailLength; i++) {
			prevX2 = tailX[i];
			prevY2 = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;
			prevX = prevX2;
			prevY = prevY2;	
		}

		switch(direction) {
			case UP: 
				headY--;
				break;
			case DOWN:
				headY++;
				break;
			case LEFT:
				headX--;
				break;
			case RIGHT:
				headX++;
				break;
		}

	}


	inline int * getTailX() { return tailX; }
	inline int * getTailY() { return tailY; }
	inline int getX() { return headX; }
	inline int getY() { return headY; }
	inline int getLength() { return tailLength; }
	inline eDir getDirection() { return direction; }
};


class cFruit {
private:
	int posX;
	int posY;

public:

	cFruit() {
		spawn();
	}

	void spawn() {
		posX = rand()%(width - 1) + 1;
		posY = rand()%(height - 1) + 1;
	}

	inline int getX() { return posX; }
	inline int getY() { return posY; }

	friend ostream & operator<<(ostream & o, cFruit c) {
		o << "Fruit: " << "[" << c.posX << ", " << c.posY << "]" << endl;
		return o;
	}
};

class cGame {

private:
	cSnake snake;
	cFruit fruit;
	int score;

public:

	cGame() {
		score = 0;
	}

	void input() {
		initscr();

	    cbreak();
	    noecho();
	    nodelay(stdscr, TRUE);

	    scrollok(stdscr, TRUE);

	    
	    if(kbhit()) {
	    	switch(getch()) {
	    		case 'w':
	    			snake.changeDirection(UP);
	    			break;
    			case 'a':
    				snake.changeDirection(LEFT);
	    			break;
    			case 's':
    				snake.changeDirection(DOWN);
	    			break;
    			case 'd':
    				snake.changeDirection(RIGHT);
	    			break;
    			case 'p':
    				over = true;
    				break;
				default:
					break;
	    	}
	    	
	    }
	    else {
	    	refresh();
	    	sleep(1);
	    }
	    
	}

	void logic() {

		snake.move();

	}

	int kbhit(void) {
	    int ch = getch();

	    if (ch != ERR) {
	        ungetch(ch);
	        return 1;
	    } else {
	        return 0;
	    }
	}

	void run() {

		while(!over) {
			draw();
			input();
			// break;
			// logic();
		}
	}

	void draw() {
		system("clear");
		int *tailX = snake.getTailX();
		int *tailY = snake.getTailY();
		for(int i = 0; i < width; i++) {
			cout << "#";
		}
		cout << endl;
		bool printed = false;
		for(int j = 0; j < height; j++) {
			for(int i = 0; i < width; i++) {
				printed = false;
				if(i == snake.getX() && j == snake.getY()) {
					cout << 'O';
					printed = true;
				}
				else if (i == fruit.getX() && j == fruit.getY()) {
					cout << 'F';
					printed = true;
				}
				else if(i == 0 || i == width - 1) {
					cout << "#";
					printed = true;
				}
				else {
					for(int t = 0; t < snake.getLength(); t++) {
						if(i == *(tailX + t) && j == *(tailY + t)) {
							cout << 'o';
							printed = true;
						}
					}
				}

				if(!printed) {
					cout << " ";
				}
			}
			cout << endl;
		}

		for(int i = 0; i < width; i++) {
			cout << "#";
		}
		cout << endl << "Score: " << score << endl;
	}

};


int main() {
	srand(time(NULL));
	// // system("clear");
	// cFruit cF;
	// cout << cF;
	// cF.spawn();
	// cout << cF;
	// cF.spawn();
	// cout << cF;
	cGame game;
	game.run();
	return 0;
}