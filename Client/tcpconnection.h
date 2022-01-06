#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

class TcpConnection : public QThread
{
    Q_OBJECT

public:
    TcpConnection(QObject *parent);
    void run();
    QTcpSocket *socket;

private:
    QByteArray m_baImage; // Variable contenant l'image reçue.
    bool m_quit; // Variable permettant de savoir que l'application est en cours de fermeture.

private slots:
    void slotQuit(); // Slot appelé lors de la fermeture de l'application.

signals:
    void signalNouvelleImage(QByteArray baImage); // Signal émis lors de la réception d'une nouvelle image.

};

#endif // TCPCONNECTION_H
