#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QImage>
#include "maze.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);

private slots:
    void loop();

signals:

private:
    void drawMaze();
    void drawUnit();
    void drawBorder();
    const QSize RESOLUTION;
    Maze m_maze;
    QTimer m_timer;
    QImage m_image;
    int m_imgWidth, m_imgHeight;
};

#endif // GAMESCENE_H
