#ifndef         __PLAZZA_HH__
#define         __PLAZZA_HH__

#include        <QMainWindow>
#include        <QtGui/QStringListModel>
#include        <QTimer>

#include        "NewCommandDialog.hh"
#include        "ui_plazza.h"
#include        <list>
#include        <iostream>
#include        <exception>
#include        <iomanip>
#include        <string>
#include        "common.hh"
#include        "Recipe.hh"
#include        "IIngredient.hh"
#include        "PizzaTaskFactory.hh"
#include        "IngredientFactory.hh"
#include        "NamedPipe.hh"
#include        "Kitchen.hh"

namespace Ui {
    class Plazza;
}

class Plazza : public QMainWindow
{
  Q_OBJECT

  public:
  explicit Plazza(QWidget * = 0, float = 1.0, int = 4, int = 1);
  ~Plazza();

private:
    void                  createKitchen();
    void                  handleCommand(std::string &);
    void                  selectAvailableKitchen();
    void                  destroyNamedPipes();
    void                  updatePizzaOrders(QListWidget *, std::list<std::string> &);
    void                  updateTable(QTableWidget *, std::map<std::string, std::string> &);
    void                  updateKitchen(NamedPipe *, NamedPipe *);
    void                  parseMapResponse(std::string &, std::map<std::string, std::string> &);
    void                  parseListResponse(std::string &, std::list<std::string> &);
    void                  refreshKitchenByName(std::string &);
    void                  deleteKitchen(std::string &);

public slots:
    void                  showCommandDialog();
    void                  quitPlazza();
    void                  refreshKitchen();
    void                  quitRequests();
    void                  changed(QListWidgetItem *item);

private:
  float                   _cookingTimeMult;
  int                     _cookPerKitchen;
  int                     _respawnFoodTime;
  NamedPipe               *_selectedKitchenW;
  NamedPipe               *_selectedKitchenR;

  Ui::Plazza              *_ui;

    Recipe                  _recipe;
    std::list<NamedPipe *>  _readPipes;
    std::list<NamedPipe *>  _writePipes;

    QTimer                  *_timer;
    QTimer                  *_timerQuit;
    std::string             _currentKitchenViewed;
};

#endif
