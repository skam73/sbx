#include "snake.h"
#include <QTime>
#include <QTimer>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QDebug>

Snake::Snake(QWidget *parent) : QWidget(parent),
                                m_timer(new QTimer),
                                m_state(GAME_INIT),
                                m_direct(MOVE_NONE),

                                m_timerMove(new QTimer),
                                trigger(false)
{
    // this->setObjectName(QStringLiteral("Snake"));
    this->setWindowTitle("Snake");
    this->resize(400, 420);

    lblCounter = new QLabel(this);
    lblCounter->setGeometry(QRect(0, 400, 400, 20));
    lblCounter->setAlignment(Qt::AlignCenter);
    QFont fnt;
    fnt.setBold(true);
    lblCounter->setFont(fnt);

    lblTime = new QLabel(this);
    lblTime->setGeometry(QRect(0, 150, 400, 90));
    lblTime->setAlignment(Qt::AlignCenter);

    fnt.setPointSize(40);
    fnt.setWeight(75);
    lblTime->setFont(fnt);

    lblTime->setText("Snake");
    lblCounter->setText("Start - ENTER  Pause - SPACE  Exit - ESC");
    lblCounter->setVisible(true);

    m_width = this->frameSize().width();
    m_seed = new quint16[m_width / m_step];

    this->setFixedSize(m_width, m_width + 20);

    connect(m_timer, &QTimer::timeout, this, &Snake::display);
    connect(m_timerMove, &QTimer::timeout, this, &Snake::move);
}

Snake::~Snake()
{
    delete lblCounter;
    delete lblTime;
    delete m_seed;
    delete m_timer;

    delete m_timerMove;
}

void Snake::display()
{
    QString count = lblTime->text();
    if (count == "Go!")
    {
        lblTime->setVisible(false);
        m_timer->stop();
        initGame();
        initTarget();

        lblCounter->setText(QString::number(0));
        lblCounter->setVisible(true);

        m_state = GAME_RUN;
        update();

        m_timerMove->start(Snake::m_delay);
    }
    else
    {
        int c = count.toInt() - 1;
        lblTime->setText(c == 0 ? QString("Go!") : QString::number(c));
    }
}

void Snake::startGame()
{
    lblCounter->setText(QString::number(0));
    lblCounter->setVisible(false);
    lblTime->setVisible(true);
    lblTime->setText(QString::number(3));

    m_timerMove->stop();
    m_direct = MOVE_NONE;
    m_state = GAME_INIT;
    m_field.clear();
    update();
    m_timer->start(1000);
}

void Snake::initGame()
{
    m_field.clear();
    m_field.reserve((m_width / m_step) * (m_width / m_step));
    for (quint16 i = 1; i <= m_size; i++)
    {
        m_field.push_back(QPoint(m_step * i, m_step));
    }
    for (quint16 i = 1; i < m_width / m_step; i++)
    {
        m_seed[i] = i * 10;
    }
}

template <typename T>
T Snake::getNumber(T limit, T offset) const
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
    T number = static_cast<T>(qrand() % limit + offset);
    return number;
}

void Snake::initTarget()
{
    static quint16 positionPre;
    bool success = false;

    do
    {
        quint16 index = getNumber(m_width / m_step - 1, 1);
        quint16 position = m_seed[index];

        if (position == positionPre)
            continue;

        positionPre = position;

        QPoint topLeft(position, position);
        QPoint topRight(position + 10, position);
        QPoint bottomLeft(position, position + 10);
        QPoint bottomRight(position + 10, position + 10);

        bool collision = false;

        for (const QPoint& point : m_field)
        {
            if (point == topLeft || point == topRight || point == bottomLeft || point == bottomRight)
            {
                collision = true;
                break;
            }
        }

        if (!collision)
        {
            m_target.setTopLeft(topLeft);
            m_target.setTopRight(topRight);
            m_target.setBottomLeft(bottomLeft);
            m_target.setBottomRight(bottomRight);

            quint16 positionX = m_seed[getNumber(m_width / m_step - 1, 1)];
            quint16 positionY = m_seed[getNumber(m_width / m_step - 1, 1)];

            m_target.moveTo(positionX - 5, positionY - 5);

            success = true;
        }
    } while (!success);
}

void Snake::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    static bool trigger = true;

    m_paint.begin(this);
    m_paint.setRenderHint(QPainter::Antialiasing);

    if (m_state == GAME_INIT)
    {
    }
    else if (m_state == GAME_RUN)
    {
        m_paint.setPen(QPen(Qt::black, m_step, Qt::SolidLine, Qt::FlatCap));
        m_paint.drawPoints(m_field.data(), m_field.size());

        m_paint.setPen(Qt::red);
        m_paint.setBrush(Qt::red);
        m_paint.drawEllipse(m_target);
    }
    else if (m_state == GAME_OVER)
    {
        if (trigger)
        {
            m_paint.setPen(QPen(Qt::lightGray, Snake::m_step, Qt::SolidLine, Qt::FlatCap));
            m_paint.drawPoints(m_field.data(), m_field.size());

            m_paint.setPen(Qt::lightGray);
            m_paint.setBrush(Qt::lightGray);
            m_paint.drawEllipse(m_target);

            trigger = false;
        }
        else
        {
            m_paint.setPen(QPen(Qt::transparent, Snake::m_step, Qt::SolidLine, Qt::FlatCap));
            m_paint.drawPoints(&m_field[0], m_field.size());
            m_paint.eraseRect(m_target);

            trigger = true;
        }
        QTimer::singleShot(500, this, SLOT(update()));
    }

    m_paint.end();
}

void Snake::evalGame(const QPoint &pointNext)
{
    if (m_field.contains(pointNext))
    {
        m_state = GAME_OVER;
        m_timerMove->stop();
        lblTime->setVisible(true);
        lblTime->setText(":(");
        lblCounter->setText("Start - ENTER  Pause - SPACE  Exit - ESC");       
    }
}

void Snake::evalTarget()
{
    QPoint point;

    if (m_target.contains(m_field.last()))
    {
        quint8 counter = lblCounter->text().toUInt();
        counter++;
        lblCounter->setText(QString::number(counter));

        switch (m_direct)
        {
            case MOVE_LEFT:
                point = QPoint(m_field.last().x() - Snake::m_step, m_field.last().y());
                break;
            case MOVE_RIGHT:
                point = QPoint(m_field.last().x() + Snake::m_step, m_field.last().y());
                break;
            case MOVE_UP:
                point = QPoint(m_field.last().x(), m_field.last().y() - Snake::m_step);
                break;
            case MOVE_DOWN:
                point = QPoint(m_field.last().x(), m_field.last().y() + Snake::m_step);
                break;
            case MOVE_NONE:
                break;
        }

        m_field.push_back(point);
        initTarget();
    }
}

void Snake::move()
{
    QPoint point;
    QPoint pointNext;

    evalTarget();
    point = m_field.last();

    switch (m_direct)
    {
        case MOVE_LEFT:
        {
            if (m_field.first().x() == Snake::m_step)
            {
                std::reverse(m_field.begin(), m_field.end());
            }
            pointNext = QPoint((point.x() > 0 + Snake::m_step) ? point.x() - Snake::m_step : m_width - Snake::m_step, point.y());
            break;
        }
        case MOVE_RIGHT:
        {
            pointNext = QPoint((point.x() < m_width - Snake::m_step) ? point.x() + Snake::m_step : 0 + Snake::m_step, point.y());
            break;
        }
        case MOVE_UP:
        {
            pointNext = QPoint(point.x(), (point.y() > 0 + Snake::m_step) ? point.y() - Snake::m_step : m_width - Snake::m_step);
            break;
        }
        case MOVE_DOWN:
        {
            pointNext = QPoint(point.x(), (point.y() < m_width - Snake::m_step) ? point.y() + Snake::m_step : 0 + Snake::m_step);
            break;
        }
        default:
        {
            return;
        }
    }

    evalGame(pointNext);

    if (m_state != GAME_OVER)
    {
        m_field.erase(m_field.begin());
        m_field.push_back(pointNext);
    }

    update();
}

void Snake::keyPressEvent(QKeyEvent *event)
{
    if (m_state == GAME_RUN)
    {
        switch (event->key())
        {
            case Qt::Key_Left:
                if (m_direct != MOVE_RIGHT)
                    m_direct = MOVE_LEFT;
                break;
            case Qt::Key_Right:
                if (m_direct != MOVE_LEFT)
                    m_direct = MOVE_RIGHT;
                break;
            case Qt::Key_Up:
                if (m_direct != MOVE_DOWN)
                    m_direct = MOVE_UP;
                break;
            case Qt::Key_Down:
                if (m_direct != MOVE_UP)
                    m_direct = MOVE_DOWN;
                break;
            case Qt::Key_Space:
                if (!trigger)
                {
                    trigger = true;
                    m_timerMove->stop();
                }
                else
                {
                    trigger = false;
                    m_timerMove->start(Snake::m_delay);
                }
                break;
            default:
                // m_direct = MOVE_NONE;
                break;
        }
    }
    if( (event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)){
        startGame();
    }
    else if (event->key() == Qt::Key_Escape)
    {
        QCoreApplication::quit();
    }
}