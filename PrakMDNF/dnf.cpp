#include "dnf.h"
#include "ui_dnf.h"

DNF::DNF(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DNF)
{
    ui->setupUi(this);
}
int DNF::exec()
{
    /*ui->spinBox->setValue(0);
    ui->spinBox->setMaximum(count);
    ui->textEdit->clear();
    ui->textEdit->setFocus();*/
    ui->tableWidget->clear();
    ui->tableWidget->setFocus();
    return QDialog::exec();
}
DNF::~DNF()
{
    delete ui;
}
