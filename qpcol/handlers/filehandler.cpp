#include "filehandler.h"

FileHandler::FileHandler(QObject *parent) : QObject(parent)
{
    m_Parent = parent;
}

FileHandler::~FileHandler()
{
    m_Parent = 0;
    delete m_Parent;
}

