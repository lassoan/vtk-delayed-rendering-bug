#include <QApplication>
#include <QSurfaceFormat>
#include <QTimer>
#include <QtDebug>

#include <QVTKOpenGLWidget.h>
#include <QVTKOpenGLNativeWidget.h>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNew.h>
#include <vtkRenderer.h>
#include <vtkVersion.h>

///////////////////////////////////////////////
// Comment/uncomment the following lines to
// experiment with different configurations:

#define USE_NATIVE_WIDGET
//#define USE_COMPATIBILITY_PROFILE

///////////////////////////////////////////////

int main(int argc, char *argv[])
{
    auto fmt = QVTKOpenGLWidget::defaultFormat();

#ifdef USE_COMPATIBILITY_PROFILE
    qDebug() << "Use compatibility profile";
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
#endif
    
    QSurfaceFormat::setDefaultFormat(fmt);

    QApplication app(argc, argv);

    vtkNew<vtkRenderer> renderer;

    vtkNew<vtkGenericOpenGLRenderWindow> window;
    window->AddRenderer(renderer);

#ifdef USE_NATIVE_WIDGET
    QVTKOpenGLNativeWidget widget;
#else
    QVTKOpenGLWidget widget;
#endif

#if VTK_MAJOR_VERSION >= 9 || (VTK_MAJOR_VERSION >= 8 && VTK_MINOR_VERSION >= 3)
    widget.setRenderWindow(window);
#else
    widget.SetRenderWindow(window);
#endif

    QTimer::singleShot(3000, [&window, &renderer]() {
        qDebug() << "Setting background to red and rendering";
        renderer->SetBackground(1.0, 0.0, 0.0);
        window->Render();
    });

    QTimer::singleShot(6000, [&window, &renderer]() {
      qDebug() << "Render again";
      window->Render();
    });

    widget.show();

    return app.exec();
}
