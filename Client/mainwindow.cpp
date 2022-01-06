#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QTime>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TcpConnection *thread = new TcpConnection(this);
    connect(thread, SIGNAL(signalNouvelleImage(QByteArray)), this, SLOT(slotNouvelleImage(QByteArray)));
    connect(this, SIGNAL(signalQuit()), thread, SLOT(slotQuit()));
    thread->start();
}

MainWindow::~MainWindow()
{
    emit(signalQuit());

    QTime dieTime = QTime::currentTime().addMSecs( 100 );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
    delete ui;
}

void MainWindow::on_leClient_returnPressed()
{
    /*m_client->sendMessage(ui->leClient->text());
    ui->lstClient->addItem(ui->leClient->text());
    ui->leClient->clear();*/
}

void MainWindow::slotNouvelleImage(QByteArray baImage)
{
    QPixmap pixImage;
    QImage image;

    if (!pixImage.loadFromData(baImage, "JPG"))
        return;
    image = pixImage.toImage();
    if (image.pixel(image.width() - 1, image.height() - 1 ) == 4286611584 &&
            image.pixel(image.width() / 2, image.height() - 1) == 4286611584  &&
            image.pixel(0, image.height() - 1) == 4286611584)
        return;

    pixImage = pixImage.scaled(ui->lbl_image->width(), ui->lbl_image->width() , Qt::KeepAspectRatio);
    ui->lbl_image->setPixmap(pixImage);
}
