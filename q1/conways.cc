#include <iostream>
#include <string>

//figure out how to trail spaces


char **readGrid(int &numRows, int &numCols) {
    std::string line;

    std::getline(std::cin, line);

    numCols = line.length();
    int capacity = 4;
    numRows = 0;

    char **grid = new char *[capacity]();

    while (true) {
        if (numRows == capacity) {
            capacity *= 2;
            char **tempGrid = new char *[capacity];
            for (int i = 0; i < numRows; ++i) {
                tempGrid[i] = grid[i];
            }
            delete[] grid;
            grid = tempGrid;
        }
        grid[numRows] = new char[numCols];
        for (int i = 0; i < numCols; ++i) {
            grid[numRows][i] = line[i];
        }
        numRows++;

        std::getline(std::cin, line);

        if (line.find('x') != std::string::npos) {
            break;
        }
    }
    return grid;
}
void destroyGrid(char **grid, int &numRows, int &numCols) {
    for (int i = 0; i < numRows; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

char **update(char **grid, int &numRows, int &numCols) {
    char **newGrid = new char*[numRows];

    for (int i = 0; i < numRows; ++i) {
        newGrid[i] = new char[numCols];
    }

    for(int r = 0; r < numRows; ++r) {
        for(int c = 0; c < numCols; ++c) {
            int alive = 0;
            for(int dr = -1; dr <= 1; dr++) {
                for(int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) continue;
                    int nr = dr + r;
                    int nc = dc + c;
                    if(nr >= 0 && nr < numRows && nc >= 0 && nc < numCols) {
                        if (grid[nr][nc] == 'O') {
                            ++alive;
                        }
                    }
                }
            }
            if (grid[r][c] == 'O' && (alive < 2 || alive > 3)) {
                newGrid[r][c]  = '.';  
            }
            else if (grid[r][c]  == '.' && alive == 3) {
                newGrid[r][c] = 'O';
            }
            else {
                newGrid[r][c]  = grid[r][c];
            }
        }
    }
    destroyGrid(grid, numRows, numCols);
    return newGrid;
}

void printGrid(char **grid, int &numRows, int &numCols) {
    if(!grid) return;
    // Print grid with border
    for (int i = 0; i < numCols; ++i) {
        std::cout << '|';
    }
    std::cout << '\n';
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            std::cout << grid[i][j];
        }
        std::cout << '\n';
    }
    for (int i = 0; i < numCols; ++i) {
        std::cout << '|';
    }
    std::cout << '\n';
}

int main() {
        int numRows = 0;
        int numCols = 0;
        char **grid = readGrid(numRows, numCols);
        
        char c;
        while(std::cin.get(c)) {
            if(c == 'p') {
                printGrid(grid, numRows, numCols);
            }
            else if (c == 's') {
                grid = update(grid, numRows, numCols);
            }
        }
        destroyGrid(grid, numRows, numCols);
        return 0;
}
