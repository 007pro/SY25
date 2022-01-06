#include "controlwindow.h"
#include "ui_controlwindow.h"

ControlWindow::ControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlWindow)
{
    ui->setupUi(this);

    // Adding TCP Server ressources
    server = new TCPServer();
    // Server-client
    connect(server, SIGNAL(Connect()), this, SLOT(on_clientConnection()));
    connect(server, SIGNAL(Disconnect()), this, SLOT(on_clientDisconnection()));
}

ControlWindow::~ControlWindow()
{
    delete ui;
}


void ControlWindow::onFrameReady(QPixmap pixmap)
{
    //m_server->sendImageTo(pixmap);
    QPixmap scaled = pixmap.scaled(ui->label->width(), ui->label->width() , Qt::KeepAspectRatio);
    ui->label->setPixmap(scaled);
    QByteArray bImage;
    QBuffer bBuffer(&bImage);
    // Putting every image in the buffer
    bBuffer.open(QIODevice::ReadWrite);
    pixmap.save(&bBuffer, "jpg");
    // Sending to TCPServer function to display the image
    server->is_newImg(bImage);
}

void ControlWindow::on_startBtn_clicked()
{
    emit startCamera();
}

void ControlWindow::on_fullFpsBtn_clicked()
{
    emit setCameraFullFPS();
}

void ControlWindow::on_lowFPSBtn_clicked()
{
    emit setCameraLowFPS();
}

void ControlWindow::on_stopBtn_clicked()
{
    emit stopCamera();
}
