#include <QApplication>
#include <QSurfaceFormat>
#include <QTimer>
#include <QtDebug>

#include <QVTKOpenGLWidget.h>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNew.h>
#include <vtkRenderer.h>

int main(int argc, char *argv[])
{
    auto format = QVTKOpenGLWidget::defaultFormat();

    //format.setProfile(QSurfaceFormat::CompatibilityProfile);

    QSurfaceFormat::setDefaultFormat(format);

    QApplication app(argc, argv);

    vtkNew<vtkRenderer> renderer;

    vtkNew<vtkGenericOpenGLRenderWindow> window;
    window->AddRenderer(renderer);

    QVTKOpenGLWidget widget;
    widget.SetRenderWindow(window);

    QTimer::singleShot(2000, [&window, &renderer]() {
        qDebug() << "Setting background to red and rendering";
        renderer->SetBackground(1.0, 0.0, 0.0);
        window->Render();
        //window->Render();
    });

    widget.show();

    return app.exec();
}
