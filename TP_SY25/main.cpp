#include "controlwindow.h"
#include "cameracontroller.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Création de la fenêtre principale
    ControlWindow w;

    //Création du controller de caméra et de son thread associé
    CameraController controller;
    QThread t;
    controller.moveToThread(&t);

    //Connection des signaux/slots
    QObject::connect(&w, &ControlWindow::startCamera, &controller, &CameraController::startCamera);
    QObject::connect(&w, &ControlWindow::stopCamera, &controller, &CameraController::stopCamera);
    QObject::connect(&w, &ControlWindow::setCameraFullFPS, &controller, &CameraController::setCameraFullFPS);
    QObject::connect(&w, &ControlWindow::setCameraLowFPS, &controller, &CameraController::setCameraLowFPS);
    QObject::connect(&controller, &CameraController::frameReady, &w, &ControlWindow::onFrameReady);

    //start thread controller
    t.start();
    //visualisation de la fenêtre principale
    w.show();

    return a.exec();
}
