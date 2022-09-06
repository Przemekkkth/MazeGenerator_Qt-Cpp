#include "gamescene.h"
#include <QGraphicsPixmapItem>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent), RESOLUTION(800, 600)
{
    setSceneRect(0,0, RESOLUTION.width(), RESOLUTION.height());
    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(50);
    m_imgWidth = (m_maze.pathWidth()+1)*m_maze.mazeWidth();
    m_imgHeight = (m_maze.pathWidth()+1)*m_maze.mazeHeight();
    m_image = QImage(m_imgWidth, m_imgHeight, QImage::Format_RGB32);
    m_image.fill(QColor(Qt::white));
}

void GameScene::loop()
{
    m_maze.updateMaze();
    clear();
    drawMaze();
    drawUnit();
    drawBorder();
    QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem(QPixmap::fromImage(m_image.scaled(RESOLUTION.width(), RESOLUTION.height())));
    addItem(pItem);
}

void GameScene::drawMaze()
{
    for(int x = 0; x < m_maze.mazeWidth(); x++)
    {
        for(int y = 0; y < m_maze.mazeHeight(); y++)
        {
            // Each cell is inflated by m_nPathWidth, so fill it in
            for(int py = 0; py < m_maze.pathWidth(); py++)
            {
                for(int px = 0; px < m_maze.pathWidth(); px++)
                {
                    if (m_maze.maze()[y * m_maze.mazeWidth() + x] & int(Maze::CELL_TYPE::CELL_VISITED) )
                    {
                        //====>Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, PIXEL_SOLID, FG_WHITE); // Draw Cell
                        m_image.setPixelColor(x * (m_maze.pathWidth() + 1) + px, y * (m_maze.pathWidth() + 1) + py, QColor(Qt::white));
                    }
                    else
                    {
                        //====>Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, PIXEL_SOLID, FG_BLUE); // Draw Cell
                        m_image.setPixelColor(x * (m_maze.pathWidth() + 1) + px, y * (m_maze.pathWidth() + 1) + py, QColor(Qt::blue));
                    }
                }
            }
            // Draw passageways between cells
            for (int p = 0; p < m_maze.pathWidth(); p++)
            {
                if (m_maze.maze()[y * m_maze.mazeWidth() + x] & int(Maze::CELL_TYPE::CELL_PATH_S) )
                {
                    //Draw(x * (m_nPathWidth + 1) + p, y * (m_nPathWidth + 1) + m_nPathWidth); // Draw South Passage
                    m_image.setPixelColor(x * (m_maze.pathWidth() + 1) + p, y * (m_maze.pathWidth() + 1) + m_maze.pathWidth(), QColor(Qt::black));
                }
                if (m_maze.maze()[y * m_maze.mazeWidth() + x] & int(Maze::CELL_TYPE::CELL_PATH_E) )
                {
                    //Draw(x * (m_nPathWidth + 1) + m_nPathWidth, y * (m_nPathWidth + 1) + p); // Draw East Passage
                    m_image.setPixelColor(x * (m_maze.pathWidth() + 1) + m_maze.pathWidth(), y * (m_maze.pathWidth() + 1) + p, QColor(Qt::black));
                }
            }
        }
    }
}

void GameScene::drawUnit()
{
    for (int py = 0; py < m_maze.pathWidth(); py++)
        for (int px = 0; px < m_maze.pathWidth(); px++)
        {
            //Draw(m_stack.top().first * (m_nPathWidth + 1) + px, m_stack.top().second * (m_nPathWidth + 1) + py, 0x2588, FG_GREEN); // Draw Cell
            m_image.setPixelColor(m_maze.stack().top().first * (m_maze.pathWidth() + 1) + px, m_maze.stack().top().second * (m_maze.pathWidth() + 1) + py, QColor(Qt::green));
        }
}

void GameScene::drawBorder()
{
    QColor borderColor = QColor(Qt::red);
    //left
    for(int i = 0; i < m_maze.mazeHeight()*(m_maze.pathWidth()+1); ++i)
    {
        m_image.setPixelColor(0, i, borderColor);
    }
    //right
    for(int i = 0; i < m_maze.mazeHeight()*(m_maze.pathWidth()+1); ++i)
    {
        m_image.setPixelColor(m_maze.mazeWidth()*(m_maze.pathWidth()+1)-1, i, borderColor);
    }
    //top
    for(int i = 0; i < m_maze.mazeWidth()*(m_maze.pathWidth()+1); ++i)
    {
        m_image.setPixelColor(i, 0, borderColor);
    }
    //bottom
    for(int i = 0; i < m_maze.mazeWidth()*(m_maze.pathWidth()+1); ++i)
    {
        m_image.setPixelColor(i, m_maze.mazeHeight()*(m_maze.pathWidth()+1)-1, borderColor);
    }
}
