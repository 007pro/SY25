#include "tcpconnection.h"

TcpConnection::TcpConnection(QObject *parent)
{
    m_quit = 0;
}

void TcpConnection::run()
{
    socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1", 5555);
    socket->write(new char[4]{1,2,3,4});
    QByteArray buffer;
    while(m_quit == 0)
    {
        if (socket->waitForReadyRead(3000))
        {
            buffer.append(socket->readAll());
            if (buffer.right(2)[0] == 0xff && buffer.right(2)[1] == 0xd9) // Les fichiers finissent par FFD9, donc vérification du JPG
            {
                emit signalNouvelleImage(buffer);
                buffer.clear();
            }
        }
    }
}

void TcpConnection::slotQuit()
{
    m_quit = 1;
}
