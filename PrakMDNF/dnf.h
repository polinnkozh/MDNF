#ifndef DNF_H
#define DNF_H

#include <QDialog>

namespace Ui {
class DNF;
}

class DNF : public QDialog
{
    Q_OBJECT

public:
    explicit DNF(QWidget *parent = nullptr);
    ~DNF();
    int exec();
    using QDialog::exec;

private:
    Ui::DNF *ui;
};

#endif // DNF_H
