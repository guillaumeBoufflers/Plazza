#include "Plazza.hh"

Plazza::Plazza(QWidget *parent, float cookingTimeMult, int cookPerKitchen, int respawnFoodTime) :  QMainWindow(parent), _cookingTimeMult(cookingTimeMult), _cookPerKitchen(cookPerKitchen), _respawnFoodTime(respawnFoodTime), _selectedKitchenW(NULL), _selectedKitchenR(NULL), _ui(new Ui::Plazza) {
  this->_ui->setupUi(this);
  this->_recipe.openIt();

  QObject::connect(this->_ui->actionQuit, SIGNAL(triggered()), this, SLOT(quitPlazza()));
  QObject::connect(this->_ui->actionNew_command, SIGNAL(triggered()), this, SLOT(showCommandDialog()));
  QObject::connect(this->_ui->kitchenList, SIGNAL(itemClicked(QListWidgetItem *)), SLOT(changed(QListWidgetItem *)));

  QStringList labelsCooks;
  labelsCooks << "Cook :" << "Status :";
  this->_ui->cooksTable->setColumnCount(2);
  this->_ui->cooksTable->setHorizontalHeaderLabels(labelsCooks);
  this->_ui->cooksTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
  this->_ui->cooksTable->verticalHeader()->hide();
  this->_ui->cooksTable->setShowGrid(false);

  QStringList labelsIngredients;
  labelsIngredients << "Ingredient :" << "Quantity :";
  this->_ui->ingredientsTable->setColumnCount(2);
  this->_ui->ingredientsTable->setHorizontalHeaderLabels(labelsIngredients);
  this->_ui->ingredientsTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
  this->_ui->ingredientsTable->verticalHeader()->hide();
  this->_ui->ingredientsTable->setShowGrid(false);

  this->_timer = new QTimer(this);
  QObject::connect(this->_timer, SIGNAL(timeout()), this, SLOT(refreshKitchen()));
  this->_timer->start(1000);

//  this->_timerQuit = new QTimer(this);
//  QObject::connect(this->_timerQuit, SIGNAL(timeout()), this, SLOT(quitRequests()));
//  this->_timerQuit->start(3000);
}

  Plazza::~Plazza() {
    delete this->_ui;
    this->destroyNamedPipes();
  }

  void          Plazza::quitPlazza() {
      std::list<NamedPipe *>::iterator itW;
      for (itW = this->_writePipes.begin(); itW != this->_writePipes.end(); ++itW) {
          (*itW)->write("r: quit");
      }
      qApp->quit();
  }

void          Plazza::quitRequests() {
      std::cout << "QUIT REQUESTS START" << std::endl;
      std::list<NamedPipe *>::iterator itW;
      std::list<NamedPipe *>::iterator itR;
      std::string tmp;

      itR = this->_readPipes.begin();
      for (itW = this->_writePipes.begin(); itW != this->_writePipes.end(); ++itW) {
          (*itW)->write("r: rquit");
          (*itR)->read(tmp);
          std::cout << "REPONSE : " << tmp << std::endl;
          if (atoi(tmp.c_str()) > 5) {

          }
          ++itR;
      }
      std::cout << "QUIT REQUESTS END" << std::endl;
}

void            Plazza::deleteKitchen(std::string &name) {
    std::cout << "Je supprime la cuisine " << name << std::endl;
}

void            Plazza::refreshKitchen() {
  if (!this->_currentKitchenViewed.empty()) {
    std::cout << "[Info] : Refreshing kitchen \"" << this->_currentKitchenViewed << "\"" << std::endl;
    this->refreshKitchenByName(this->_currentKitchenViewed);
  }
}

void            Plazza::changed(QListWidgetItem *item) {
  if (item) {
    this->_timer->stop();
    this->_currentKitchenViewed = item->text().toStdString();
    this->refreshKitchen();
    this->_timer->start(1000);
  }
}

void            Plazza::refreshKitchenByName(std::string &name) {
  NamedPipe   *write = NULL;
  NamedPipe   *read = NULL;

  if (!this->_writePipes.empty() && !this->_readPipes.empty()) {
    for (std::list<NamedPipe *>::iterator it = this->_readPipes.begin(); it != this->_readPipes.end(); ++it) {
      if ((*it)->getName() == name + "-w") {
	read = *it;
      }
    }
    for (std::list<NamedPipe *>::iterator it2 = this->_writePipes.begin(); it2 != this->_writePipes.end(); ++it2) {
      if ((*it2)->getName() == name + "-r") {
	write = *it2;
      }
    }
    if (write == NULL || read == NULL)
      std::cerr << "[Error] : An error occured while refreshing Qt." << std::endl;
    else {
      this->_ui->kitchenName->setText(QString::fromStdString(name));
      this->updateKitchen(write, read);
    }
  }
}

void            Plazza::parseMapResponse(std::string &str, std::map<std::string, std::string> &stringMap)
{
  size_t	a = 0;
  std::string	tmp(str);
  std::string	tmp1, tmp2;

  if (tmp != " ")
    {
      while (tmp.size() > 0)
	{
	  a = tmp.find(' ');
	  tmp1 = tmp.substr(0, a);
	  tmp.erase(0, tmp1.size());
	  a = tmp.find(';');
	  tmp2 = tmp.substr(0, a);
	  stringMap[tmp1] = tmp2;
	  tmp.erase(0, tmp2.size() + 1);
	}
    }
}

void            Plazza::parseListResponse(std::string &str, std::list<std::string> &list)
{
  size_t	a = 0;
  std::string	tmp(str);
  std::string	tmp1;

  if (tmp != " ")
    {
      while (tmp.size() > 0)
	{
	  a = tmp.find(';');
	  tmp1 = tmp.substr(0, a);
	  list.push_front(tmp1);
	  tmp.erase(0, tmp1.size() + 1);
	}
    }
}

void            Plazza::updateKitchen(NamedPipe *write, NamedPipe *read) {
  std::string tmp;

  // First step : Updating ingredient list.
  std::map<std::string, std::string> ingredientMap;
  write->write("r: nbIngredients");
  read->read(tmp);
  this->parseMapResponse(tmp, ingredientMap);
  this->updateTable(this->_ui->ingredientsTable, ingredientMap);

  // Second step : Updating cooks
  tmp.clear();
  std::map<std::string, std::string> cookStatus;
  write->write("r: cookStatus");
  read->read(tmp);
  this->parseMapResponse(tmp, cookStatus);
  this->updateTable(this->_ui->cooksTable, cookStatus);

  // Third step : Updating awaiting/processing/finished pizzas
  std::list<std::string> awaitingPizzas;
  std::list<std::string> processingPizzas;
  std::list<std::string> finishedPizzas;

  tmp.clear();
  write->write("r: awaitingList");
  read->read(tmp);
  this->parseListResponse(tmp, awaitingPizzas);
  this->_ui->totalAwaiting->setText(QString::fromStdString("(Total " + intToString(awaitingPizzas.size()) + ")"));
  this->updatePizzaOrders(this->_ui->awaitingOrdersList, awaitingPizzas);

  tmp.clear();
  write->write("r: processingList");
  read->read(tmp);
  this->parseListResponse(tmp, processingPizzas);
  this->_ui->totalProcessing->setText(QString::fromStdString("(Total " + intToString(processingPizzas.size()) + ")"));
  this->updatePizzaOrders(this->_ui->processingOrdersList, processingPizzas);

  tmp.clear();
  write->write("r: finishedList");
  read->read(tmp);
  this->parseListResponse(tmp, finishedPizzas);
  this->_ui->totalFinished->setText(QString::fromStdString("(Total " + intToString(finishedPizzas.size()) + ")"));
  this->updatePizzaOrders(this->_ui->finishedOrdersList, finishedPizzas);
}

void            Plazza::showCommandDialog() {
  std::list<std::string> list;

  NewCommandDialog dialog(this->_recipe, &list);
  dialog.exec();
  for (std::list<std::string>::iterator it = list.begin(); it != list.end(); ++it) {
    this->handleCommand(*it);
  }
}

void            Plazza::updatePizzaOrders(QListWidget *widget, std::list<std::string> &strings) {
  if (widget && widget->count())
    widget->clear();
  if (widget && !strings.empty()) {
    for (std::list<std::string>::iterator it = strings.begin(); it != strings.end(); ++it) {
      widget->addItem(QString::fromStdString(*it));
    }
  }
}

void            Plazza::updateTable(QTableWidget *widget, std::map<std::string, std::string> &strings) {
  if (widget && widget->rowCount())
    for (int i= widget->rowCount() - 1; i >= 0; --i)
      widget->removeRow(i);
  if (widget && !strings.empty()) {
    for (std::map<std::string, std::string>::iterator it = strings.begin(); it != strings.end(); ++it) {
      int row = widget->rowCount();
      widget->setRowCount(row);
      widget->insertRow(row);
      widget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString((*it).first)));
      widget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString((*it).second)));
    }
  }
}

void            Plazza::createKitchen() {
  pid_t         pid;
  NamedPipe     *write;
  NamedPipe     *read;
  std::string   name = "kitchen-" + intToString(this->_readPipes.size());

  std::cout << "[Info] : New kitchen created : " << name << std::endl;
  pid = fork();
  if (pid == -1)
    throw new PlazzaException("Cannot fork");
  if (pid == 0) {
    Kitchen *kitchen = new Kitchen(name, this->_cookPerKitchen, &(this->_recipe), this->_cookingTimeMult, this->_respawnFoodTime);
    if (kitchen)
      kitchen->run();
    exit(0);
  } else {
    write = new NamedPipe(name + "-r");
    read = new NamedPipe(name + "-w");
    this->_writePipes.push_back(write);
    this->_readPipes.push_back(read);
    this->_ui->kitchenList->addItem(QString::fromStdString(name));
  }
}

void            Plazza::selectAvailableKitchen() {
  std::list<NamedPipe *>::iterator itW;
  std::list<NamedPipe *>::iterator itR;
  std::string tmp;
  int         current((this->_cookPerKitchen * 2) + 1);

  itR = this->_readPipes.begin();
  for (itW = this->_writePipes.begin(); itW != this->_writePipes.end(); ++itW) {
    std::cout << "[Info] : Asking \"" << (*itW)->getName() << "\" kitchen if available ..." << std::endl;
    (*itW)->write("r: nbAwaiting");
    if ((*itR)->read(tmp)) {
      if (atoi(tmp.c_str()) < current) {
	// Faire ici la requete pour savoir si il y a assez d'ingrédients.
	current = atoi(tmp.c_str());
	this->_selectedKitchenW = *itW;
	this->_selectedKitchenR = *itR;
      }
    }
    ++itR;
  }
}

void            Plazza::handleCommand(std::string &command) {
  std::string tmp;

  this->_selectedKitchenW = NULL;
  this->_selectedKitchenR = NULL;
  this->selectAvailableKitchen();
  if (this->_selectedKitchenW == NULL) {
    std::cout << "[Info] : No kitchen available. Creating a new kitchen ..." << std::endl;
    this->createKitchen();
    this->selectAvailableKitchen();
    if (!this->_selectedKitchenW || !this->_selectedKitchenR)
      throw new PlazzaException("Cannot create kitchen");
  }
  this->_selectedKitchenW->write(command);
  this->_selectedKitchenR->read(tmp);
  if (tmp == PIZZA_NO) {
      this->createKitchen();
      this->selectAvailableKitchen();
      if (this->_selectedKitchenW != NULL) {
          this->_selectedKitchenW->write(command);
          this->_selectedKitchenR->read(tmp);
          if (tmp == PIZZA_NO)
            std::cout << "[Warning] : An uknown error occured. Your order was canceled." << std::endl;
      } else
        std::cout << "[Warning] : An uknown error occured. Your order was canceled." << std::endl;
  }
}

void            Plazza::destroyNamedPipes() {
  std::list<NamedPipe *>::iterator itW;
  std::list<NamedPipe *>::iterator itR;

  for (itW = this->_writePipes.begin(); itW != this->_writePipes.end(); ++itW) {
    (*itW)->destroy();
  }
  for (itR = this->_readPipes.begin(); itR != this->_readPipes.end(); ++itR) {
    (*itR)->destroy();
  }
}
