#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>

class JanelaCrudFilmes : public QWidget {
public:
    JanelaCrudFilmes() {
        setWindowTitle("Buscador e Gerenciador de Filmes");
        resize(800, 600);

        QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);

        QHBoxLayout *layoutBusca = new QHBoxLayout();
        QLineEdit *campoBusca = new QLineEdit();
        campoBusca->setPlaceholderText("Buscar filme por título, diretor ou ID...");
        QPushButton *btnBuscar = new QPushButton("Pesquisar");
        
        layoutBusca->addWidget(campoBusca);
        layoutBusca->addWidget(btnBuscar);
        layoutPrincipal->addLayout(layoutBusca);

        QTableWidget *tabelaFilmes = new QTableWidget(0, 4); 
        tabelaFilmes->setHorizontalHeaderLabels({"ID", "Título", "Ano", "Gênero"});
        tabelaFilmes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tabelaFilmes->setSelectionBehavior(QAbstractItemView::SelectRows);
        
        layoutPrincipal->addWidget(tabelaFilmes);

        QHBoxLayout *layoutFormulario = new QHBoxLayout();
        QLineEdit *inputTitulo = new QLineEdit();
        inputTitulo->setPlaceholderText("Título do Filme");
        QLineEdit *inputAno = new QLineEdit();
        inputAno->setPlaceholderText("Ano de Lançamento");
        QLineEdit *inputGenero = new QLineEdit();
        inputGenero->setPlaceholderText("Gênero");

        layoutFormulario->addWidget(inputTitulo);
        layoutFormulario->addWidget(inputAno);
        layoutFormulario->addWidget(inputGenero);
        layoutPrincipal->addLayout(layoutFormulario);

        QHBoxLayout *layoutBotoes = new QHBoxLayout();
        QPushButton *btnAdicionar = new QPushButton("Adicionar Novo");
        QPushButton *btnAtualizar = new QPushButton("Atualizar Selecionado");
        QPushButton *btnExcluir = new QPushButton("Excluir Selecionado");

        btnExcluir->setStyleSheet("background-color: #d9534f; color: white; font-weight: bold;");
        btnAdicionar->setStyleSheet("background-color: #5cb85c; color: white; font-weight: bold;");

        layoutBotoes->addWidget(btnAdicionar);
        layoutBotoes->addWidget(btnAtualizar);
        layoutBotoes->addWidget(btnExcluir);
        layoutPrincipal->addLayout(layoutBotoes);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    JanelaCrudFilmes janela;
    janela.show();
    
    return app.exec();
}