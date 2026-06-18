#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QLabel label("Qt está funcionando corretamente!");
    label.resize(400, 100);
    label.show();
    
    return app.exec();
}