#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <fstream>
#include <vector>
#include <string>


#include "filmes.h"
#include "arvore_b_plus.h"
#include "indice_invertido.h"

class JanelaBuscador : public QWidget {
    Q_OBJECT 

private:
    
    QLineEdit *campoBusca;
    QPushButton *btnBuscar;
    QTableWidget *tabelaFilmes;
    QLabel *lblStatus;

    
    ArvoreBPlus *arvore;
    IndiceInvertido *indice;
    std::fstream arquivo_dados;

public:
    JanelaBuscador(QWidget *parent = nullptr) : QWidget(parent) {
        
        arvore = new ArvoreBPlus(50); 
        indice = new IndiceInvertido(arvore);

        
        setWindowTitle("Buscador de Filmes");
        resize(950, 600);

        
        QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);

        
        QLabel *lblTitulo = new QLabel("Buscador de Filmes");
        lblTitulo->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 5px;");
        layoutPrincipal->addWidget(lblTitulo);

        
        QHBoxLayout *layoutBusca = new QHBoxLayout();

        campoBusca = new QLineEdit();
        campoBusca->setPlaceholderText("Digite palavras-chave para a busca (ex: star wars)...");
        campoBusca->setStyleSheet("padding: 8px; font-size: 14px; border: 1px solid #ccc; border-radius: 4px;");

        btnBuscar = new QPushButton("Pesquisar");
        btnBuscar->setStyleSheet("background-color: #007acc; color: white; font-weight: bold; padding: 8px 25px; font-size: 14px; border-radius: 4px;");

        layoutBusca->addWidget(campoBusca, 5); 
        layoutBusca->addWidget(btnBuscar, 1);
        layoutPrincipal->addLayout(layoutBusca);

        
        tabelaFilmes = new QTableWidget(0, 7);
        tabelaFilmes->setHorizontalHeaderLabels({"ID", "Título", "Ano", "Gênero", "Nota IMDB", "Duração", "Diretor"});
        tabelaFilmes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tabelaFilmes->setSelectionBehavior(QAbstractItemView::SelectRows);
        tabelaFilmes->setEditTriggers(QAbstractItemView::NoEditTriggers); 
        layoutPrincipal->addWidget(tabelaFilmes);

        
        lblStatus = new QLabel("Inicializando...");
        lblStatus->setStyleSheet("color: #7f8c8d; font-style: italic;");
        layoutPrincipal->addWidget(lblStatus);

        
        connect(btnBuscar, &QPushButton::clicked, this, &JanelaBuscador::executarBusca);
        connect(campoBusca, &QLineEdit::returnPressed, this, &JanelaBuscador::executarBusca);

        
        carregarBancoDados();
    }

    ~JanelaBuscador() {
        if (arquivo_dados.is_open()) {
            arquivo_dados.close();
        }
        delete indice;
        delete arvore;
    }

private:
    
    void carregarBancoDados() {
        lblStatus->setText("Carregando e indexando os registros na memória...");

        
        arquivo_dados.open("filmes.dat", std::ios::in | std::ios::out | std::ios::binary);

        
        if (!arquivo_dados.is_open()) {
            arquivo_dados.clear();
            arquivo_dados.open("filmes.dat", std::ios::out | std::ios::binary);
            arquivo_dados.close();
            arquivo_dados.open("filmes.dat", std::ios::in | std::ios::out | std::ios::binary);
        }

        arquivo_dados.clear();
        arquivo_dados.seekg(0, std::ios::beg);

        Filme f;
        int rrn = 0;
        int filmes_carregados = 0;

        
        while (f.ler(arquivo_dados)) {
            std::string titulo = f.obter_titulo();
            indice->adicionarRegistro(rrn, titulo);
            filmes_carregados++;
            rrn++;
        }

        arquivo_dados.clear();
        arquivo_dados.seekg(0, std::ios::beg);

        lblStatus->setText("Pronto! " + QString::number(filmes_carregados) + " filmes carregados com sucesso.");
    }

    
    void executarBusca() {
        
        QString textoBusca = campoBusca->text().trimmed();

        if (textoBusca.isEmpty()) {
            QMessageBox::warning(this, "Aviso", "O campo de busca não pode estar vazio!");
            return;
        }

        
        tabelaFilmes->setRowCount(0);
        lblStatus->setText("Buscando por: '" + textoBusca + "'...");

        
        std::string termoStd = textoBusca.toStdString();
        std::vector<int> resultados = indice->buscar(termoStd);

        if (resultados.empty()) {
            lblStatus->setText("Nenhum filme encontrado para: '" + textoBusca + "'");
            return;
        }

        int linha = 0;
        Filme f;

        
        for (int rrn : resultados) {
            if (f.ler_rrn(arquivo_dados, rrn)) {
                tabelaFilmes->insertRow(linha);

                
                tabelaFilmes->setItem(linha, 0, new QTableWidgetItem(QString::fromUtf8(f.obter_id())));
                tabelaFilmes->setItem(linha, 1, new QTableWidgetItem(QString::fromUtf8(f.obter_titulo())));
                tabelaFilmes->setItem(linha, 2, new QTableWidgetItem(QString::number(f.obter_ano())));
                tabelaFilmes->setItem(linha, 3, new QTableWidgetItem(QString::fromUtf8(f.obter_genero())));

                
                if (f.obter_nota() < 0) {
                    tabelaFilmes->setItem(linha, 4, new QTableWidgetItem("N/A"));
                } else {
                    tabelaFilmes->setItem(linha, 4, new QTableWidgetItem(QString::number(f.obter_nota(), 'f', 1)));
                }

                tabelaFilmes->setItem(linha, 5, new QTableWidgetItem(QString::number(f.obter_duracao_min()) + " min"));
                tabelaFilmes->setItem(linha, 6, new QTableWidgetItem(QString::fromUtf8(f.obter_diretor())));

                linha++;
            }
        }

        lblStatus->setText("Busca concluída: " + QString::number(linha) + " filme(s) encontrado(s).");
    }
};


#include "main_qt.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    JanelaBuscador janela;
    janela.show();

    return app.exec();
}