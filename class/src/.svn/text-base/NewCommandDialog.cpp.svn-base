#include "NewCommandDialog.hh"
#include "ui_newcommanddialog.h"

NewCommandDialog::NewCommandDialog(Recipe &recipe, std::list<std::string> *list, QWidget *parent) : QDialog(parent), _ui(new Ui::NewCommandDialog), _list(list) {
    this->_ui->setupUi(this);

    std::map<std::string, std::vector<ingredientTypes> > pizzas = recipe.getPizzas();
    for (std::map<std::string, std::vector<ingredientTypes> >::const_iterator it = pizzas.begin(); it != pizzas.end(); ++it) {
        QString qstr = QString::fromStdString((*it).first);
        this->_ui->comboBox->addItem(qstr);
    }
    this->_ui->spinBox->setMaximum(20);
    this->_ui->spinBox->setMinimum(1);
}

NewCommandDialog::~NewCommandDialog() {
    delete this->_ui;
}

void        NewCommandDialog::accept() {
    int     i(0);

    while (i < this->_ui->spinBox->value()) {
        this->_list->push_back("c: " + this->_ui->comboBox->currentText().toStdString() + " " + this->_ui->comboBox_2->currentText().toStdString());
        i++;
    }
    this->done(QDialog::Accepted);
}

void        NewCommandDialog::reject() {
    this->done(QDialog::Rejected);
}
