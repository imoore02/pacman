#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <algorithm>

const int GRID_SIZE = 10;
const int CELL_SIZE = 40;

struct Cell {
    int row;
    int col;
    bool isObstacle;
    bool isOpen;
    int gScore;
    int fScore;
    Cell* cameFrom;
};

int calculateManhattanDistance(Cell* cellA, Cell* cellB) {
    return std::abs(cellB->row - cellA->row) + std::abs(cellB->col - cellA->col);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(GRID_SIZE * CELL_SIZE, GRID_SIZE * CELL_SIZE), "Pathfinding");

    std::vector<std::vector<Cell>> grid(GRID_SIZE, std::vector<Cell>(GRID_SIZE));

    int startRow = 2;
    int startCol = 2;
    int endRow = 8;
    int endCol = 8;

    for (int row = 0; row < GRID_SIZE; ++row) {
        for (int col = 0; col < GRID_SIZE; ++col) {
            grid[row][col].row = row;
            grid[row][col].col = col;
            grid[row][col].isObstacle = false;
            grid[row][col].isOpen = false;
            grid[row][col].gScore = INT_MAX;
            grid[row][col].fScore = INT_MAX;
            grid[row][col].cameFrom = nullptr;
        }
    }

    grid[startRow][startCol].isObstacle = false;
    grid[endRow][endCol].isObstacle = false;

    std::vector<Cell*> openSet;
    std::vector<Cell*> closedSet;
    openSet.push_back(&grid[startRow][startCol]);
    grid[startRow][startCol].isOpen = true;
    grid[startRow][startCol].gScore = 0;
    grid[startRow][startCol].fScore = calculateManhattanDistance(&grid[startRow][startCol], &grid[endRow][endCol]);

    while (!openSet.empty()) {
        Cell* current = openSet[0];
        int currentIndex = 0;
        for (int i = 1; i < openSet.size(); ++i) {
            if (openSet[i]->fScore < current->fScore) {
                current = openSet[i];
                currentIndex = i;
            }
        }

        openSet.erase(openSet.begin() + currentIndex);
        closedSet.push_back(current);

        if (current == &grid[endRow][endCol]) {
            std::vector<Cell*> path;
            Cell* pathCell = current;
            while (pathCell != nullptr) {
                path.push_back(pathCell);
                pathCell = pathCell->cameFrom;
            }

            for (Cell* pathCell : path) {
                sf::RectangleShape cellShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                cellShape.setPosition(pathCell->col * CELL_SIZE, pathCell->row * CELL_SIZE);
                cellShape.setFillColor(sf::Color::Green);
                window.draw(cellShape);
            }

            break;
        }

        std::vector<Cell*> neighbors;
        if (current->row > 0)
            neighbors.push_back(&grid[current->row - 1][current->col]);
        if (current->row < GRID_SIZE - 1)
            neighbors.push_back(&grid[current->row + 1][current->col]);
        if (current->col > 0)
            neighbors.push_back(&grid[current->row][current->col - 1]);
        if (current->col < GRID_SIZE - 1)
            neighbors.push_back(&grid[current->row][current->col + 1]);

        for (Cell* neighbor : neighbors) {
            if (neighbor->isObstacle || std::find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end()) {
                continue;
            }

            int tentativeGScore = current->gScore + 1;
            bool isNewNeighbor = std::find(openSet.begin(), openSet.end(), neighbor) == openSet.end();

            if (isNewNeighbor || tentativeGScore < neighbor->gScore) {
                neighbor->gScore = tentativeGScore;
                neighbor->fScore = neighbor->gScore + calculateManhattanDistance(neighbor, &grid[endRow][endCol]);
                neighbor->cameFrom = current;

                if (!neighbor->isOpen) {
                    openSet.push_back(neighbor);
                    neighbor->isOpen = true;
                }
            }
        }

        // Clear the window
        window.clear();

        // Draw the grid cells
        for (int row = 0; row < GRID_SIZE; ++row) {
            for (int col = 0; col < GRID_SIZE; ++col) {
                sf::RectangleShape cellShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                cellShape.setPosition(col * CELL_SIZE, row * CELL_SIZE);

                if (grid[row][col].isObstacle) {
                    cellShape.setFillColor(sf::Color::Black);
                } else if (grid[row][col].isOpen) {
                    cellShape.setFillColor(sf::Color::Blue);
                } else {
                    cellShape.setFillColor(sf::Color::White);
                }

                window.draw(cellShape);
            }
        }

        // Display the window contents
        window.display();
    }

    // Main loop for handling events
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    return 0;
}
