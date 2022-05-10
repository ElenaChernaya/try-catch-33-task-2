#include <iostream>
#include <ctime>
#include <exception>

class Winner: public std::exception
{
    const char* what() const noexcept override
    {
        return "Your win!";
    }
};


class Loss: public std::exception
{
    const char* what() const noexcept override
    {
        return "Your lost!";
    }
};


class CoordinateCorrectness: public std::exception
{
    const char* what() const noexcept override
    {
        return "Invalid coordinates.";
    }
};


class Field
{
    char field[3][3];
    int x = 0;
    int y = 0;

public:

    //формирование игрового поля
    void create()
    {
        for(int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                field[i][j] = '.';
            }
        }

        std::srand(std::time(nullptr));
        x = rand()%3;
        y = rand()%3;
        field[x][y] = 'f';

        int count = 0;
        while(count < 3)
        {
            std::srand(std::time(nullptr));
            x = rand()%3;
            y = rand()%3;

            if(field[x][y] == '.')
            {
                field[x][y] = 's';
                count++;
            }
        }
    }

    //проверка ходов игрока
    bool shot(int& x, int& y, bool& ok)
    {
        if (x < 0 || x > 2 || y < 0 || y > 2)
        {
            throw CoordinateCorrectness();
            ok = true;
        }

        if (field[x][y] == 'f')
        {
            ok = false;
            throw Winner();
        }

        if (field[x][y] == 's')
        {
            ok = false;
            throw Loss();
        }

        if (field[x][y] == '.')
        {
            ok = true;
        }

        return ok;
    }

    //вывод поля на экран
    void print()
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                std::cout << field[i][j];
            } std::cout << std::endl;
        }
    }
};



int main() {
    Field game;
    game.create();
    std::cout << std::endl;
    game.print();

    int x, y;
    int number = 0; //кол-во ходов
    bool ok = true;
    while(ok)
    {
        std::cout << "\nYour turn!\n";
        std::cin >> x >> y;

        try
        {
            if (game.shot(x, y, ok))
            {
                ++number;
                std::cout << "Past!" << std::endl;
                std::cout << "Number of attempts: "<< number << std::endl;
            }
        }

        catch(const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }

        catch(const std::invalid_argument& arg)
        {
            std::cerr << arg.what() << std::endl;
        }
    }
}