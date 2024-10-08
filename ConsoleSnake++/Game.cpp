#include <windows.h>
#include <iostream>
#include <conio.h>
#include <ctime>

bool gameOver;
const int width = 50; //Ширина карты
const int height = 20; //Высота карты
int x, y, fruitX, fruitY, score; //Координаты змеи X/Y, координаты фруктов X/Y
int tailX[100], tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;


void Setup() //Выставление параметров
{
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw() //Рисование карты
{
	Sleep(100); //Скорость змеи
	system("cls");
	for (int i = 0; i < width + 1; i++)
	{
		std::cin.tie(0);
		std::cout << "X";
	}
	std::cout << std::endl;
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cin.tie(0);
			if (j == 0 || j == width - 1)std::cout << "X";
			if (i == y && j == x)std::cout << "0";
			else if (i == fruitY && j == fruitX)std::cout << "@";
			else 
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						std::cout << "o";

					}
				}
				if (!print)
				{
					std::cout << " ";
				}
			}
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < width + 1; i++)
	{
		std::cin.tie(0);
		std::cout << "X";
	}
	std::cout << std::endl;
	std::cout << "Score: " << score << std::endl;
	std::cout << "Press 'x' to close the game\n\n\n";
	

}
void Input() //Отслежка нажатий клавиатуры
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break; 
		}
	}
}

void Logic() //Логика игры
{
	int prevX = tailX[0]; 
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	
	switch (dir)
	{
	case LEFT:x--; 
		break;
	case RIGHT:x++;
		break;
	case UP:y--;
		break;
	case DOWN:y++;
		break;
	}
	if (x > width || x < 0 || y > height || y < 0)
	gameOver = true;
	
	if (x == fruitX && y == fruitY){
		score += 5;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
	}
}
