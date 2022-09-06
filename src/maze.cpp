#include "maze.h"
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>

Maze::Maze()
{
    init();
}

void Maze::init()
{
    m_nMazeWidth = 40;
    m_nMazeHeight = 25;
    m_maze = new int[m_nMazeWidth*m_nMazeHeight];
    memset(m_maze, 0x00, m_nMazeWidth*m_nMazeHeight*sizeof(int));
    m_nPathWidth = 20;

    //Choose a starting cell
    int x = rand() % m_nMazeWidth;
    int y = rand() % m_nMazeHeight;
    m_stack.push(std::make_pair(x, y));
    m_maze[y * m_nMazeWidth + x] = int(CELL_TYPE::CELL_VISITED);
    m_nVisitedCells = 1;
}

void Maze::updateMaze()
{
    auto offset = [&](int x, int y)
    {
        return (m_stack.top().second + y) * m_nMazeWidth + (m_stack.top().first + x);
    };

    // Do Maze Algorithm
    if (m_nVisitedCells < m_nMazeWidth * m_nMazeHeight)
    {
        // Create a set of unvisted neighbours
        std::vector<int> neighbours;

        // North neighbour
        if (m_stack.top().second > 0 && (m_maze[offset(0, -1)] & int(CELL_TYPE::CELL_VISITED) ) == 0)
            neighbours.push_back(0);
        // East neighbour
        if (m_stack.top().first < m_nMazeWidth - 1 && (m_maze[offset(1, 0)] & int(CELL_TYPE::CELL_VISITED) ) == 0)
            neighbours.push_back(1);
        // South neighbour
        if (m_stack.top().second < m_nMazeHeight - 1 && (m_maze[offset(0, 1)] & int(CELL_TYPE::CELL_VISITED) ) == 0)
            neighbours.push_back(2);
        // West neighbour
        if (m_stack.top().first > 0 && (m_maze[offset(-1, 0)] & int(CELL_TYPE::CELL_VISITED) ) == 0)
            neighbours.push_back(3);

        // Are there any neighbours available?
        if (!neighbours.empty())
        {
            // Choose one available neighbour at random
            int next_cell_dir = neighbours[rand() % neighbours.size()];

            // Create a path between the neighbour and the current cell
            switch (next_cell_dir)
            {
            case 0: // North
                m_maze[offset(0, -1)] |= int(CELL_TYPE::CELL_VISITED) | int(CELL_TYPE::CELL_PATH_S);
                m_maze[offset(0,  0)] |= int(CELL_TYPE::CELL_PATH_N);
                m_stack.push(std::make_pair((m_stack.top().first + 0), (m_stack.top().second - 1)));
                break;

            case 1: // East
                m_maze[offset(+1, 0)] |= int(CELL_TYPE::CELL_VISITED) | int(CELL_TYPE::CELL_PATH_W);
                m_maze[offset( 0, 0)] |= int(CELL_TYPE::CELL_PATH_E);
                m_stack.push(std::make_pair((m_stack.top().first + 1), (m_stack.top().second + 0)));
                break;

            case 2: // South
                m_maze[offset(0, +1)] |= int(CELL_TYPE::CELL_VISITED) | int(CELL_TYPE::CELL_PATH_N);
                m_maze[offset(0,  0)] |= int(CELL_TYPE::CELL_PATH_S);
                m_stack.push(std::make_pair((m_stack.top().first + 0), (m_stack.top().second + 1)));
                break;

            case 3: // West
                m_maze[offset(-1, 0)] |= int(CELL_TYPE::CELL_VISITED) | int(CELL_TYPE::CELL_PATH_E);
                m_maze[offset( 0, 0)] |= int(CELL_TYPE::CELL_PATH_W);
                m_stack.push(std::make_pair((m_stack.top().first - 1), (m_stack.top().second + 0)));
                break;

            }

            m_nVisitedCells++;
        }
        else
        {
            // No available neighbours so backtrack!
            m_stack.pop();
        }
    }
}

int Maze::mazeWidth() const
{
    return m_nMazeWidth;
}

int Maze::mazeHeight() const
{
    return m_nMazeHeight;
}

int *Maze::maze() const
{
    return m_maze;
}

int Maze::visitedCells() const
{
    return m_nVisitedCells;
}

int Maze::pathWidth() const
{
    return m_nPathWidth;
}

std::stack<std::pair<int, int> > Maze::stack() const
{
    return m_stack;
}
