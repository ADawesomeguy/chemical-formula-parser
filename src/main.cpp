#include "chemparse.hpp"
#include "rang.hpp"

#include <climits>

void waitForExit() {
  std::cout << std::endl;
  std::cout
      << "PLEASE PRESS ENTER OR CLOSE THE WINDOW TO TERMINATE THE PROGRAM:"
      << std::endl;
  std::cin.clear();
  std::cin.ignore(INT_MAX, '\n');
  std::cin.get();
}

int main() {
  while (true) {
    std::cout << "> ";

    std::string chemFormula;
    std::cin >> chemFormula;

    if (chemFormula == "exit") {
      std::cout << std::endl << "Exiting..." << std::endl;
      exit(0);
    }

    std::vector<chemparse::Element> elements =
        chemparse::parseFormulaToElements(chemFormula);
    if (elements.empty()) {
      std::cout << "Invalid or empty formula." << std::endl;
      continue;
    } else if (elements.size() == 1) {
      chemparse::Element element = elements[0];
      std::cout << element.name << " (" << element.symbol << ")"
                << ": " << std::endl
                << "Atomic Number: " << element.atomicNumber << std::endl
                << "Atomic Mass: " << element.atomicMass << " amu" << std::endl
                << "Molar Mass: " << element.molarMass << " g/mol" << std::endl
                << "Discoverer: " << element.discoverer << std::endl
                << "Appearance: " << element.appearance << std::endl
                << std::endl
                << "(HINT: 0 or empty values mean unknown or simply not in "
                   "this database)"
                << std::endl;
    } else {
      for (chemparse::Element &element : elements) {
        long amount = element.amount;
        std::string symbol = element.symbol;
        std::string name = element.name;
        std::string isOrAre = (amount == 1 ? "is" : "are");
        std::cout << "There " << isOrAre << " " << amount << " " << name << " ("
                  << symbol << ")" << std::endl;
      }

      chemparse::Compound compound(elements);
      compound.getMolarMass();
      std::cout << std::endl;
      std::cout << "The total molar mass is: " << compound.getMolarMass()
                << " g/mol" << std::endl;
      std::cout << "The total atomic mass is: " << compound.getMolarMass()
                << " amu" << std::endl;
    }
  }
}