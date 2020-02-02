# include <iostream>
# include <ctime>

using namespace std;

class cFruit {
private:
	int posX;
	int posY;

public:

	cFruit(int w, int h) {
		spawn(w, h);
	}

	void spawn(int w, int h) {
		posX = rand()%(w - 1) + 1;
		posY = rand()%(h - 1) + 1;
	}

	inline int getX() { return posX; }
	inline int getY() { return posY; }

	friend ostream & operator<<(ostream & o, cFruit c) {
		o << "Fruit: " << "[" << c.posX << ", " << c.posY << "]" << endl;
		return o;
	}
};


int main() {
	srand(time(NULL));
	cFruit cF(50, 50);
	cout << cF;
	cF.spawn(50, 50);
	cout << cF;
	cF.spawn(50, 50);
	cout << cF;
	return 0;
}