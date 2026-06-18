#include <QApplication>
#include <QLabel>
#include "arvore_b_plus.h"
#include "indice_invertido.h"
#include "filmes.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QLabel label("Qt está funcionando corretamente!");
    label.resize(400, 100);
    label.show();
    
    return app.exec();
}