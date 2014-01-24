#ifndef NEWCOMMANDDIALOG_H
#define NEWCOMMANDDIALOG_H

#include <QDialog>
#include "Recipe.hh"

namespace Ui {
class NewCommandDialog;
}

class NewCommandDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewCommandDialog(Recipe &, std::list<std::string> *, QWidget *parent = 0);
    ~NewCommandDialog();

public slots:
    void        accept();
    void        reject();
    
private:
    Ui::NewCommandDialog *_ui;
    std::list<std::string> *_list;
};

#endif // NEWCOMMANDDIALOG_H
