#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QDialog>
#include <vector>
#include <set>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setButtonsEnabled();
    setWindowTitle("Построение МДНФ");
}
void MainWindow::setButtonsEnabled()
{
    ui->spinBox->setValue(2);
    ui->spinBox->setMaximum(6);
    ui->spinBox->setMinimum(2);
    ui->spinBox_2->setValue(0);
    ui->spinBox_2->setMaximum(1000000000);
    ui->spinBox_2->setMinimum(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
QString mas[10000][1000];
QString func;
int indx = 0;
int C (int n, int k) {
    int num = 1, den = 1, k1 = k;
    k = n - k;
    while (n > k) {
        num *= n;
        --n;
    }
    while (k1) {
        den *= k1;
        --k1;
    }
    int ans = num / den;
    return ans;
}
//int prevAmountOfColumns = 0;
void MainWindow::createUI(const QStringList headers, const int amountOfColumns, const int amountOfVars, const int amountOfRiad)
{
    //~QTableWidget ();
    for (int i = 0; i < 8; ++i) {
        ui->tableWidget->removeColumn(amountOfColumns);
    }
    //ui->tableWidget->clear();
    //ui->tableWidget->setFocus();
    //ui->tableWidget->clearContents();
    ui->tableWidget->setColumnCount(amountOfColumns + 1);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    QString x; QChar a = 'b'; x += a;
    //QTableWidgetItem *item = new QTableWidgetItem(x);
    /*for (int i = 0; i < 8; ++i) {
        ui->tableWidget->insertRow(i);
        for (int j = 0; j <= amountOfColumns; ++j) {
            ui->tableWidget->setItem(i,j, new QTableWidgetItem(x));
        }
    }*/
    for (int j = 0; j < amountOfColumns + 1; ++j) {
        ui->tableWidget->insertRow(j);
        for (long long i = 0; i < amountOfRiad; ++i) {
            //QString s = "1̶";
            QTableWidgetItem *item = new QTableWidgetItem(mas[i][j]);
            //item->;
            ui->tableWidget->setItem(j,i, item);
            //ui->tableWidget->item(j,i)->setBackground(Qt::red);
            //std::cout << mas[i][j] << " " ;
            //qDebug() << i << j << mas[i][j];
        }
        //std::cout << std::endl;
    }

}
std::vector <QString> header;
void fulfill (QStringList& list, int iters, int maxi, QString cur) {
    if (!iters) {
        list << cur;
        header.push_back(cur);
        return;
    }
    int i; QChar x = 'a';
    if (cur.size() == 0) i = x.unicode();
    else i = cur[cur.size()-1].unicode() + 1;
    for (;i<maxi; ++i) {
        fulfill(list,iters-1,maxi,cur + QChar(i));
    }
}
QStringList createHeaders (int n) {
    QStringList ans;
    /*for (int i = 0; i < n; ++i) {
        QChar val = 'a';
        val += i;
        QString temp;
        temp += val;
        ans << temp;
    }*/
    QChar x = 'a';
    int maxi = x.unicode();
    maxi += n;
    QString cur;
    for (int i = 1; i <= n; ++i) {
        fulfill(ans,i,maxi,cur);
    }
    ans << "f";
    return ans;
}
int amount (int n) {
    int ans = 0;
    for (long long i = 1; i <= n; ++i) {
        ans += C(n,i);
    }
    return ans;
}
std::vector <int> indexes;
int num = 0;
void fulfillColumn (int numOfColumn) {
    for (int i = 0; i < 100; ++i) {
        QString ans;
        for (auto u:indexes) {
            ans += mas[u][i];
        }
        mas[numOfColumn][i] = ans;
    }
}
void fulfillMas (int last, int iter, int n) {
    if (last != -1) {
        indexes.push_back(last);
    }
    if (iter == 0) {
        fulfillColumn(num);
        /*for (auto u:indexes) {
            std::cout << u << " ";
        }*/
        //std::cout << std::endl;
        indexes.pop_back();
        ++num;
        return;
    }
    for (int x = last + 1; x < n; ++x) {
        fulfillMas(x,iter-1,n);
    }
    if (last != -1) {
        indexes.pop_back();
    }
}
void fulfillFirstElements(int last, int iter, int n) {
    if (last != -1) {
        indexes.push_back(last);
    }
    if (iter == 0) {
        for (int i = 0; i < indexes.size(); ++i) {
            QString r;
            QChar temp = '0';
            r+=QChar(indexes[i]+temp.unicode());
            mas[i][num] = r;
            //std::cout << i << " " << num <<" "<< mas[i][num] << std::endl;
        }
        /*for (auto u:indexes) {
            std::cout << u << " ";
        }*/
        //std::cout << std::endl;
        indexes.pop_back();
        ++num;
        return;
    }
    for (int x = 0; x < 2; ++x) {
        fulfillFirstElements(x,iter-1,n);
    }
    if (last != -1) {
        indexes.pop_back();
    }
}
QString ToDv (int num, int riad) {
    QString ans;
    int iter = 0;
    while (num > 0) {
        ans += char((num%2)+int('0'));
        num /=2;
        ++iter;
    }
    while (iter < riad) {
        ans += '0';
        ++iter;
    }
    std::reverse(ans.begin(),ans.end());
    return ans;
}
bool strokaSoderjitsyaVstroke (QString s1, QString s2) {
    int iii = 0;
    for (int i = 0; i < s1.size(); ++i) {
        if (iii < s2.size()) {
            if (s2[iii] == s1[i]) {
            ++iii;
            }
        }
    }
    if (iii == s2.size()) {
        return 1;
    } else return 0;
}
bool sravnenie (QString x) {
    if (x == "a̶" || x == "b̶" || x == "c̶" || x == "d̶" || x == "e̶" || x == "f̶" || x=="g̶" ) {
        return 1;
    }
    return 0;
}
std::vector <std::vector<QString>> answers;
std::vector <QString> currentStrs;
std::vector <QString> finals;
int element = 0;
void findOptimalAnswers (long long el) {
    if (el == element) {
        std::set <QString> st;
        for (auto u:currentStrs) {
            st.insert(u);
        }
        QString fin;
        for (auto u:st) {
            fin += u;
            fin += 'V';
        }
        fin[fin.size() - 1] = ' ';
        finals.push_back(fin);
        return;
    }
    for (auto u:answers[el]) {
        currentStrs.push_back(u);
        findOptimalAnswers(el + 1);
        currentStrs.pop_back();
    }
}
QString symb (QChar x) {
    if (x == 'a') return "a̶";
            else if (x == 'b') return "b̶";
            else if (x == 'c') return "c̶";
            else if (x == 'd') return "d̶";
            else if (x == 'e') return "e̶";
            else if (x == 'f') "f̶";
            return "g̶";
}
int amountOfVars, valueOfFunction, amountOfColumns, riad;
std::vector <std::vector<QString>> toDelete;
bool used[1000][1000] = {0};
void MainWindow::on_pushButton_clicked()
{
    ++indx;
    if (indx == 1) {
    amountOfVars = ui->spinBox->value();
    valueOfFunction = ui->spinBox_2->value();
    amountOfColumns = amount(amountOfVars);
    riad = 1;
    for (int i = 0; i < amountOfVars; ++i) {
        riad *= 2;
    }
    toDelete.resize(riad+1);
    func = ToDv(valueOfFunction,riad);
    num = 0;
    fulfillFirstElements(-1, amountOfVars, amountOfVars);
    num = amountOfVars;
    for (int i = 2; i <= amountOfVars; ++i) {
        fulfillMas(-1,i,amountOfVars);
    }
    int ind = amountOfColumns;
    for (int i = 0; i < riad; ++i) {
        mas[ind][i] = func[i];
        //qDebug() << ind << i << mas[ind][i];
    }
    createUI(createHeaders(amountOfVars), amountOfColumns, amountOfVars, riad);
    ui->label_3->setText("Это таблица ДНФ");
    ui->pushButton->setText("Дальше");
    ui->spinBox->setValue(amountOfVars);
    ui->spinBox->setMaximum(amountOfVars);
    ui->spinBox->setMinimum(amountOfVars);
    ui->spinBox_2->setValue(valueOfFunction);
    ui->spinBox_2->setMaximum(valueOfFunction);
    ui->spinBox_2->setMinimum(valueOfFunction);
    } else if (indx == 2){
    for (int i = 0; i < riad; ++i) {
        if (func[i] == '0') {
            for (int j = 0; j <  amountOfColumns + 1; ++j) {
                QString h = mas[j][i];
                //toDelete[i].push_back(h);
                /*std::reverse(h.begin(),h.end());
                h+='d';
                std::reverse(h.begin(),h.end());
                mas[j][i] = h;*/
                toDelete[j].push_back(mas[j][i]);
                used[j][i] = true;
                ui->tableWidget->item(i,j)->setBackground(Qt::red);
            }
        }
    }
    ui->label_3->setText("Уберем значения, для которых функция равна 0");
    } else if (indx == 3) {
    for (int j = 0; j < amountOfColumns + 1; ++j) {
        for (auto u : toDelete[j]) {
            for (int i = 0; i < riad; ++i) {
                if (mas[j][i] == u && !used[j][i]) {
                    used[j][i] = true;
                    ui->tableWidget->item(i,j)->setBackground(Qt::red);
                }
            }
        }
    }
    ui->label_3->setText("Уберем значения, равные убранным ранее по их столбцам");
    } else if (indx == 4) {
    for (int i = 0; i < riad; ++i) {
        for (int j = 0; j < amountOfColumns; ++j) {
            for (int j1 = 0; j1 < amountOfColumns; ++j1) {
                //qDebug() << i << j << j1;

                if (j != j1 && !used[j][i] && !used[j1][i]) {
                    if (header[j].size() > header[j1].size()) {
                        if (strokaSoderjitsyaVstroke(header[j],header[j1])) {
                            used[j][i] = true;
                            ui->tableWidget->item(i,j)->setBackground(Qt::blue);
                        }
                    } else {
                        if (strokaSoderjitsyaVstroke(header[j1],header[j])) {
                            used[j1][i] = true;
                            ui->tableWidget->item(i,j1)->setBackground(Qt::blue);
                        }
                    }
                }
            }
        }
    }
    ui->label_3->setText("Уберем коньюкции");
    } else if (indx == 5) {
    answers.resize(amountOfColumns);
    for (int i = 0; i < func.size(); ++i) {
        //std::cout << i << " "<<func[i]<< std::endl;
        if (func[i] == '1') {
            for (int j = 0; j < amountOfColumns; ++j) {
                if (!used[j][i]) {
                    //std::cout << j << " " << i << " " << mas[j][i] << std::endl;
                    QString current;
                    for (int c = 0; c < mas[j][i].size(); ++c) {
                        //qDebug() << mas[j][i][c];
                        if (mas[j][i][c] == '0') {
                            /*current += "not(";
                            current += header[j][c];
                            current += ")";*/
                            current += symb(header[j][c]);
                            //qDebug() << header[j][c] << symb(header[j][c]);
                        } else {
                            current += header[j][c];
                        }
                    }
                    qDebug() <<"this "<< mas[j][i] << current;
                    //std::cout << current<<std::endl;
                    answers[element].push_back(current);
                }
            }
            ++element;
        }
    }
    findOptimalAnswers(0);
    std::set <QString> posl;
    int minimalsize = 1000000;
    for (auto u: finals) {
        long long minus = 0;
        //std::cout << u << " " << u.size() << std::endl;
        for (long long i = 0; i < u.size(); ++i) {
            if (i < u.size() - 2) {
                QString iff;
                iff += u[i];
                iff += u[i + 1];
                iff += u[i+2];
                if (sravnenie(iff)) minus += 2;
            }
            if (u[i] == 'V' || u[i] == ' ') minus += 1;
        }
        int xx = u.size(); xx -= minus;
        minimalsize = std::min(minimalsize,xx);
        posl.insert(u);
    }
    std::vector <QString> FINALLY;
    for (auto u: posl) {
        long long minus = 0;
        //std::cout << u << " " << u.size() << std::endl;
        for (long long i = 0; i < u.size(); ++i) {
            if (i < u.size() - 2) {
                QString iff;
                iff += u[i];
                iff += u[i + 1];
                iff += u[i+2];
                if (sravnenie(iff)) minus += 2;
            }
            if (u[i] == 'V' || u[i] == ' ') minus += 1;
        }
        int xx = u.size(); xx -= minus;
        if (xx == minimalsize) {
            FINALLY.push_back(u);
        }
    }
    /*QString LASt = "Возможные минимальные коньюкции: ";
    for (auto u:FINALLY) {
        LASt += u;
        LASt += ' ';
    }*/
    QString s = "Возможные минимальные коньюкции: ";
    QStringList d;
    d << s;

    ui->tableWidget_2->setColumnCount(1);
    ui->tableWidget_2->setShowGrid(true);
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_2->setHorizontalHeaderLabels(d);
    /*ui->tableWidget->insertRow(j);
    for (long long i = 0; i < amountOfRiad; ++i) {
        //QString s = "1̶";
        QTableWidgetItem *item = new QTableWidgetItem(mas[i][j]);
        //item->;
        ui->tableWidget->setItem(j,i, item);*/
    int j = 0;
    for (auto u:FINALLY) {
        //LASt += u;
        //LASt += ' ';
        qDebug() << u;
        ui->tableWidget_2->insertRow(j);
        QTableWidgetItem *item = new QTableWidgetItem(u);
        ui->tableWidget_2->setItem(j,0, item);
        ++j;
    }
    //ui->label_3->setText(LASt);
    //QMessageBox::warning(this, "Ошибка!", "Файл недоступен для чтения!");
    }

    //prevAmountOfColumns = amountOfColumns + 5;
}

