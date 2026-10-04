#include "Sudoku.hpp"
#include <iostream>

void loadSamplePuzzle(Sudoku& sudoku) {
    // Standard test puzzle
    Grid sample = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            sudoku.setCell(r, c, sample[r][c]);
        }
    }
}

void inputCustomGrid(Sudoku& sudoku) {
    sudoku.clear();
    std::cout << "\nEnter cells one by one as: <row> <col> <val> (e.g., '1 5 7' places 7 at Row 1, Col 5).\n";
    std::cout << "Enter '0 0 0' when done entering custom values.\n\n";

    while (true) {
        int r, c, val;
        std::cout << "Input (row col val): ";
        if (!(std::cin >> r >> c >> val)) break;
        if (r == 0 && c == 0 && val == 0) break;

        if (r >= 1 && r <= 9 && c >= 1 && c <= 9 && val >= 0 && val <= 9) {
            sudoku.setCell(r - 1, c - 1, val);
            sudoku.printBoard();
        } else {
            std::cout << "Invalid input range! Rows/cols must be 1-9, values 0-9.\n";
        }
    }
}

int main() {
    Sudoku sudoku;
    loadSamplePuzzle(sudoku);

    int choice = -1;
    while (choice != 0) {
        std::cout << "=============================\n";
        std::cout << "    C++ SUDOKU SOLVER CLI    \n";
        std::cout << "=============================\n";
        std::cout << "1. Display Current Board\n";
        std::cout << "2. Solve Current Board\n";
        std::cout << "3. Generate Random Puzzle\n";
        std::cout << "4. Enter Custom Board\n";
        std::cout << "5. Clear Board\n";
        std::cout << "0. Exit\n";
        std::cout << "Select Choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                sudoku.printBoard();
                break;
            case 2:
                if (!sudoku.isValidGrid()) {
                    std::cout << "\n[Error] The current board has rule conflicts! Fix them first.\n\n";
                } else {
                    std::cout << "\nSolving...\n";
                    if (sudoku.solve()) {
                        std::cout << "\n[Success] Puzzle Solved!";
                        sudoku.printBoard();
                    } else {
                        std::cout << "\n[Failed] No valid solution exists for this grid.\n\n";
                    }
                }
                break;
            case 3: {
                int diffChoice;
                std::cout << "\nSelect Difficulty (1: Easy, 2: Medium, 3: Hard): ";
                std::cin >> diffChoice;
                if (diffChoice == 1) sudoku.generatePuzzle(Difficulty::EASY);
                else if (diffChoice == 2) sudoku.generatePuzzle(Difficulty::MEDIUM);
                else sudoku.generatePuzzle(Difficulty::HARD);

                std::cout << "\nGenerated New Puzzle:";
                sudoku.printBoard();
                break;
            }
            case 4:
                inputCustomGrid(sudoku);
                break;
            case 5:
                sudoku.clear();
                std::cout << "\nBoard cleared.";
                sudoku.printBoard();
                break;
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}