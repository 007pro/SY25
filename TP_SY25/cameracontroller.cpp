#include "cameracontroller.h"
#include <QThread>
#include <QDebug>

CameraController::CameraController(QObject *parent) : QObject(parent)
{
    face_cascade.load("/home/vincent/opencv-4.x/data/haarcascades_cuda/haarcascade_frontalface_alt.xml");
    idx=0;
    count=0;
    timer = new QTimer(this);
    timer->setInterval(1000); //60FPS
    connect(timer, &QTimer::timeout, this, &CameraController::sendImage);
}

void CameraController::startCamera()
{
    running = true;
    videoCapture.open(0);
    //if(!fullfps){
    timer->start();
    //}
    if(videoCapture.isOpened()){
        runCam();
    }
    return;
}

void CameraController::stopCamera()
{
    running = false;
    timer->stop();
    videoCapture.release();
}

void CameraController::setCameraFullFPS()
{
    timer->setInterval(17); //60FPS
    count=0;
}

void CameraController::setCameraLowFPS()
{
    timer->setInterval(1000); //1FPS

}

void CameraController::runCam(){
    if(running && videoCapture.isOpened()){
        videoCapture >> image;
        cv::cvtColor(image, grey, cv::COLOR_BGR2GRAY);
        cv::resize(grey, grey, cv::Size(grey.cols/2, grey.rows/2));
        face_cascade.detectMultiScale(grey,faces);
        for(size_t i = 0; i < faces.size(); i++)
        {
            cv::Point center( faces[i].x*2 + faces[i].width, faces[i].y*2 + faces[i].height);
            ellipse( image, center, cv::Size( faces[i].width, faces[i].height), 0, 0, 360, cv::Scalar(255,0,255),4);
        }
        if(faces.size()>0){
            idx=1;
        }
        if(faces.size()==0){
            count+=1;
            if(count==120){
                idx=2;
            }
        }
        QTimer::singleShot(0, this, &CameraController::runCam);
    }
}

void CameraController::sendImage(){
    if(idx==1){
        idx=0;
        setCameraFullFPS();
    }
    if(idx==2){
        idx=0;
        setCameraLowFPS();
    }
    cv::cvtColor(image,image,cv::COLOR_BGR2RGB);
    emit frameReady(QPixmap::fromImage(QImage((unsigned char*) image.data, image.cols, image.rows, QImage::Format_RGB888)));
}

