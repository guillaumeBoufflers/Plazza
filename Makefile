##
## Makefile for plazza
##
##

NAME=		plazza

MAKEFILE_NAME=	QT_Makefile

all:		$(NAME)

$(NAME):
		qmake-qt4 -o $(MAKEFILE_NAME)
		make -f $(MAKEFILE_NAME)

clean:
		make -f $(MAKEFILE_NAME) clean


fclean:		clean
		rm -f $(NAME)


re:		fclean all
