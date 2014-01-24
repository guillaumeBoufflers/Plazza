CONFIG          +=  qt
QT              +=  core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET          =   plazza
TEMPLATE        =   app

OBJECTS_DIR     =   qt_tmp
UI_HEADERS_DIR  =   qt_tmp
MOC_DIR         =   qt_tmp

SOURCES         +=  common/src/main.cpp                     \
                    common/src/intToString.cpp              \
                    common/src/count.cpp                    \
                    common/src/split.cpp                    \
                    common/src/isANumber.cpp                \
                    common/src/stringToInt.cpp              \
                    common/src/stringToIngredient.cpp       \
                    class/src/Cook.cpp                      \
                    class/src/varCond.cpp                   \
                    class/src/NamedPipe.cpp                 \
                    class/src/Ingredient.cpp                \
                    class/src/Kitchen.cpp                   \
                    class/src/Mutex.cpp                     \
                    class/src/PizzaTask.cpp                 \
                    class/src/PizzaTaskFactory.cpp          \
                    class/src/IngredientFactory.cpp         \
                    class/src/Recipe.cpp                    \
                    class/src/Plazza.cpp                    \
                    class/src/Timer.cpp                     \
                    class/src/NewCommandDialog.cpp

HEADERS         +=  interfaces/IPizzaTask.hh                \
                    interfaces/IIngredient.hh               \
                    interfaces/ICook.hh                     \
                    interfaces/IIngredientFactory.hh        \
                    interfaces/IPizzaTaskFactory.hh         \
                    class/headers/Plazza.hh                 \
                    class/headers/varCond.hh                \
                    class/headers/Mutex.hh                  \
                    class/headers/PizzaTaskFactory.hh       \
                    class/headers/Ingredient.hh             \
                    class/headers/IngredientFactory.hh      \
                    class/headers/NamedPipe.hh              \
                    class/headers/Recipe.hh                 \
                    class/headers/NewCommandDialog.hh       \
                    class/headers/Kitchen.hh                \
                    class/headers/PizzaTask.hh              \
                    class/headers/Timer.hh                  \
                    class/headers/Cook.hh                   \
                    common/headers/common.hh                \
                    common/headers/main.hh                  \
                    exceptions/PlazzaException.hh           \

QMAKE_CXXFLAGS  += -lpthread -I interfaces/ -I class/headers/ -I common/headers -I exceptions/

FORMS           +=  ui/plazza.ui                            \
                    ui/newcommanddialog.ui
