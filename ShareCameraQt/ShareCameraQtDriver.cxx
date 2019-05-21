#include <QApplication>
#include <QDebug>
#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>

#include "ShareCameraQt.h"

//#define USE_COMPATIBILITY_PROFILE

int main( int argc, char** argv )
{
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
    auto fmt = QVTKOpenGLNativeWidget::defaultFormat();

#ifdef USE_COMPATIBILITY_PROFILE
    qDebug() << "Use compatibility profile";
    fmt.setProfile(QSurfaceFormat::CompatibilityProfile);
#endif
    
    QSurfaceFormat::setDefaultFormat(fmt);

  // QT Stuff
  QApplication app( argc, argv );
  
  ShareCameraQt shareCameraQt;
  shareCameraQt.show();
  
  return app.exec();
}
