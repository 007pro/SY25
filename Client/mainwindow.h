#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_leClient_returnPressed();
    void slotNouvelleImage(QByteArray baImage); // Slot appelé lors de la réception d'une nouvelle image.

private:
    Ui::MainWindow *ui;

    TcpClient *m_client;

signals:
    void signalQuit(); // Signal émis lors de la fermeture de l'application.
};

#endif // MAINWINDOW_H
