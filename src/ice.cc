/// Copyright 2012, (c) Daniel Fanjul Alcuten, Goran Petrovic
#include "src/ice.h"

int main(int argc, char **argv) {
  google::SetUsageMessage("Ice");
  google::ParseCommandLineFlags(&argc, &argv, true);

  // start the app
  std::cout << "Hostia puta!" << std::endl;
}
