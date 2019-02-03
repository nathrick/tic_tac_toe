#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QQmlListProperty>


class GameEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList gridModel READ getGridModel NOTIFY gridModelChanged)
    Q_PROPERTY(QString currentMove READ getCurrentMove WRITE setCurrentMove NOTIFY currentMoveChanged)
    Q_PROPERTY(int crossWins READ getCrossWins NOTIFY crossWinsChanged)
    Q_PROPERTY(int circleWins READ getCircleWins NOTIFY circleWinsChanged)

public:
    explicit GameEngine(QObject *parent = nullptr);

    Q_INVOKABLE void loadGridModel();
    QStringList getGridModel();
    QString checkWinner();

    Q_INVOKABLE void setCellState(const QString & state, int index);
    Q_INVOKABLE QString getCellState(int index);
    Q_INVOKABLE QString getPicture(const QString & state);


    QString getCurrentMove() const;
    void setCurrentMove(const QString & currentMove);

    int getCrossWins() const;
    int getCircleWins() const;

signals:
    void gridModelChanged();
    void currentMoveChanged();
    void gameFinished(QString winner);
    void crossWinsChanged();
    void circleWinsChanged();

public slots:

private:
    QStringList m_gridModel;
    QString m_currentMove;
    QString m_lastWinner;
    int m_crossWins;
    int m_circleWins;
};

#endif // GAMEENGINE_H
