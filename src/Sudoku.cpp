#include "Sudoku.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

Sudoku::Sudoku() : grid(9, std::vector<int>(9, 0)) {}

void Sudoku::clear() {
    grid = Grid(9, std::vector<int>(9, 0));
}

int Sudoku::getCell(int r, int c) const { return grid[r][c]; }
void Sudoku::setCell(int r, int c, int val) { grid[r][c] = val; }

bool Sudoku::isValid(int row, int col, int num) const {
    for (int i = 0; i < 9; ++i) {
        if (i != col && grid[row][i] == num) return false;
        if (i != row && grid[i][col] == num) return false;

        int bRow = 3 * (row / 3) + i / 3;
        int bCol = 3 * (col / 3) + i % 3;
        if ((bRow != row || bCol != col) && grid[bRow][bCol] == num) return false;
    }
    return true;
}

bool Sudoku::isValidGrid() const {
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (grid[r][c] != 0 && !isValid(r, c, grid[r][c])) {
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::solve() {
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (grid[r][c] == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (isValid(r, c, num)) {
                        grid[r][c] = num;
                        if (solve()) return true;
                        grid[r][c] = 0; // Backtrack
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::fillGridRandomly(int row, int col) {
    if (row == 9) return true;
    int nextRow = (col == 8) ? row + 1 : row;
    int nextCol = (col == 8) ? 0 : col + 1;

    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(nums.begin(), nums.end(), std::default_random_engine(seed));

    for (int num : nums) {
        if (isValid(row, col, num)) {
            grid[row][col] = num;
            if (fillGridRandomly(nextRow, nextCol)) return true;
            grid[row][col] = 0;
        }
    }
    return false;
}

void Sudoku::removeKDigits(int count) {
    int removed = 0;
    std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
    while (removed < (81 - count)) {
        int cellId = rng() % 81;
        int r = cellId / 9;
        int c = cellId % 9;
        if (grid[r][c] != 0) {
            grid[r][c] = 0;
            removed++;
        }
    }
}

void Sudoku::generatePuzzle(Difficulty difficulty) {
    clear();
    fillGridRandomly(0, 0);
    removeKDigits(static_cast<int>(difficulty));
}

void Sudoku::printBoard() const {
    std::cout << "\n  +-------+-------+-------+\n";
    for (int r = 0; r < 9; ++r) {
        std::cout << r + 1 << " | ";
        for (int c = 0; c < 9; ++c) {
            if (grid[r][c] == 0) {
                std::cout << ". ";
            } else {
                std::cout << grid[r][c] << " ";
            }
            if ((c + 1) % 3 == 0) std::cout << "| ";
        }
        std::cout << "\n";
        if ((r + 1) % 3 == 0) {
            std::cout << "  +-------+-------+-------+\n";
        }
    }
    std::cout << "    1 2 3   4 5 6   7 8 9 (Columns)\n\n";
}