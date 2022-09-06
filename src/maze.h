#ifndef MAZE_H
#define MAZE_H
#include <stack>

class Maze
{
public:
    Maze();
    enum class CELL_TYPE{
        CELL_PATH_N = 0x01,
        CELL_PATH_E = 0x02,
        CELL_PATH_S = 0x04,
        CELL_PATH_W = 0x08,
        CELL_VISITED = 0x10,
    };
private:
    int m_nMazeWidth;
    int m_nMazeHeight;
    int *m_maze;



    // Algorithm variables
    int  m_nVisitedCells;
    std::stack<std::pair<int, int>> m_stack;	// (x, y) coordinate pairs
    int  m_nPathWidth;

public:
    void init();
    void updateMaze();

    int mazeWidth() const;
    int mazeHeight() const;
    int* maze() const;

    int visitedCells() const;
    int pathWidth() const;

    std::stack<std::pair<int, int>> stack() const;
};

#endif // MAZE_H
