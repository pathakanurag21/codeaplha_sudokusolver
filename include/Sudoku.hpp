#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <vector>

using Grid = std::vector<std::vector<int>>;

enum class Difficulty { EASY = 35, MEDIUM = 30, HARD = 22 };

class Sudoku {
public:
    Sudoku();

    void clear();
    bool isValid(int row, int col, int num) const;
    bool isValidGrid() const;

    // Solver
    bool solve();

    // Generator
    void generatePuzzle(Difficulty difficulty);

    // Terminal Display & I/O
    void printBoard() const;
    void setCell(int r, int c, int val);
    int getCell(int r, int c) const;

private:
    Grid grid;
    bool fillGridRandomly(int row, int col);
    void removeKDigits(int count);
};

#endif // SUDOKU_HPP