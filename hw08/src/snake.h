#pragma once

#include <QWidget>
#include <QLabel>
#include <QPainter>

class Snake : public QWidget
{
private:
    enum direction_T
    {
       MOVE_NONE = 0,
       MOVE_LEFT = 1,
       MOVE_RIGHT = 2,
       MOVE_UP = 3,
       MOVE_DOWN = 4,
    };
    enum state_T
    {
       GAME_INIT = 0,
       GAME_RUN = 1,
       GAME_OVER = 2,
       GAME_EXIT = 3
    };

    QLabel *lblCounter;
    QLabel *lblTime;
    QTimer *m_timer;

    const static quint8 m_step = 10;
    const static quint8 m_counter = 3;
    const static quint8 m_size = 2;
    const static quint8 m_delay = 150;

    quint16 m_width;
    quint16 *m_seed;

    QVector<QPoint> m_field;
    QRect m_target;
    direction_T m_direct;
    state_T m_state;
    QPainter m_paint;


    QTimer *m_timerMove;
    bool    trigger;

protected:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

    void evalGame(const QPoint &pointNext);
    void evalTarget();
    void initGame();
    void startGame();
    void display();
    void initTarget();

    void move();

    template<typename T>
    T  getNumber(T limit, T offset) const;

public:
    Snake(QWidget *parent = 0);
    ~Snake();
};