#include 				"main.hh"

int 					main(int ac, char **av) {
  if (ac == 4) {
    try {
      QApplication	a(ac, av);
      if (!(atof(av[1]) > 0 && atoi(av[2]) && atoi(av[3]) > 1000)) {
          std::cerr << "Usage: " << av[0] << " [time_multiplicator] [cook_per_kitchen] [respawn_delay > 1000]" << std::endl;
          return (1);
      }
      try {
      Plazza 			plazza(NULL, atof(av[1]), atoi(av[2]), atoi(av[3]));
      plazza.show();
      return (a.exec());
      } catch (std::exception *e) {
          std::cerr << "An error occured : " << e->what() << std::endl;
          return (1);
      }
    } catch (...) {
      std::cerr << "An unknown error occured" << std::endl;
    }
  } else {
    std::cerr << "Usage: " << av[0] << " [time_multiplicator] [cook_per_kitchen] [respawn_delay > 1000]" << std::endl;
    return (1);
  }
}
