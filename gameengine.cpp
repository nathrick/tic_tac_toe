#include "gameengine.h"

GameEngine::GameEngine(QObject *parent) : QObject(parent)
{
    m_currentMove = QString("circle");
    m_circleWins = m_crossWins = 0;
    loadGridModel();
}

void GameEngine::loadGridModel()
{
    m_lastWinner.clear();
    m_gridModel.clear();

    for(int i = 0; i < 9; ++i)
        m_gridModel.push_back("");

    emit gridModelChanged();
}

QStringList GameEngine::getGridModel()
{
    return m_gridModel;
}

void GameEngine::setCellState(const QString & state, int index)
{
    if(m_gridModel[index].isEmpty()) //set cell new state if cell is empty
        m_gridModel[index] = state;
    else
        return;

    if(m_currentMove == "cross")    //set current move
        m_currentMove = "circle";
    else
        m_currentMove = "cross";

    checkWinner(); //check if there is a winner

    if(m_lastWinner == "cross") {   //increment counter, if cross wins
        ++m_crossWins;
        emit crossWinsChanged();
    }

    if(m_lastWinner == "circle") { //increment counter, if circle wins
        ++m_circleWins;
        emit circleWinsChanged();
    }

    emit currentMoveChanged();
    emit gridModelChanged();
}

QString GameEngine::getCellState(int index)
{
    return m_gridModel[index];
}

QString GameEngine::getPicture(const QString & state)
{
    if(state == "cross")
        return QString("cross.png");
    else if(state == "circle")
        return QString("circle.png");
    else
        return QString("");
}

QString GameEngine::getCurrentMove() const
{
    return m_currentMove;
}

void GameEngine::setCurrentMove(const QString & currentMove)
{
    m_currentMove = currentMove;
}

int GameEngine::getCrossWins() const
{
    return m_crossWins;
}

int GameEngine::getCircleWins() const
{
    return m_circleWins;
}

QString GameEngine::checkWinner()
{
    m_lastWinner = QString("");

    //rows
    if((m_gridModel[0] == m_gridModel[1]) && (m_gridModel[0] == m_gridModel[2]))
        m_lastWinner = m_gridModel[0];
    else if((m_gridModel[3] == m_gridModel[4]) && (m_gridModel[3] == m_gridModel[5]))
        m_lastWinner = m_gridModel[3];
    else if((m_gridModel[6] == m_gridModel[7]) && (m_gridModel[6] == m_gridModel[8]))
        m_lastWinner = m_gridModel[6];
    //columns
    else if((m_gridModel[0] == m_gridModel[3]) && (m_gridModel[0] == m_gridModel[6]))
        m_lastWinner = m_gridModel[0];
    else if((m_gridModel[1] == m_gridModel[4]) && (m_gridModel[1] == m_gridModel[7]))
        m_lastWinner = m_gridModel[7];
    else if((m_gridModel[2] == m_gridModel[5]) && (m_gridModel[2] == m_gridModel[8]))
        m_lastWinner = m_gridModel[2];
    //diagonals
    else if((m_gridModel[0] == m_gridModel[4]) && (m_gridModel[0] == m_gridModel[8]))
        m_lastWinner = m_gridModel[0];
    else if((m_gridModel[2] == m_gridModel[4]) && (m_gridModel[2] == m_gridModel[6]))
        m_lastWinner = m_gridModel[2];

    if((!m_gridModel.contains("")) && m_lastWinner.isEmpty()) { //check if all cells are not empty and there is no winner, set draw
        m_lastWinner = "draw";
        emit gameFinished("draw");
    }

    if(!(m_lastWinner.isEmpty())) //set winner if there is no draw
    {
        if(m_lastWinner == "cross")
            emit gameFinished("Player 'X'");
        if(m_lastWinner == "circle")
            emit gameFinished("Player 'O'");
    }

    return m_lastWinner;
}
