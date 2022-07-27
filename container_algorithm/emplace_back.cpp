#include <iostream>
#include <string>
#include <vector>

struct President {
  std::string name;
  std::string country;
  int year;

  President(std::string p_name, std::string p_country, int p_year)
      : name(std::move(p_name)), country(std::move(p_country)), year(p_year) {
    std::cout << "I am being constructed." << std::endl;
  }

  President(const President& other)
      : name(std::move(other.name)),
        country(std::move(other.country)),
        year(other.year) {
    std::cout << "I am being copy constructed." << std::endl;
  }

  President(President&& other)
      : name(std::move(other.name)),
        country(std::move(other.country)),
        year(other.year) {
    std::cout << "I am being moved." << std::endl;
  }

  President& operator=(const President& other);
};

int main() {
  std::vector<President> elections;
  std::cout << std::endl << "emplace_back:" << std::endl;
  elections.emplace_back("Nelson Mandela", "South Africa", 1994);

  std::vector<President> reElections;
  std::cout << std::endl << "push_back:" << std::endl;
  reElections.push_back(President("Franklin Delno Roosevelt", "the USE", 1936));

  std::cout << std::endl << "contents: " << std::endl;
  for (const President& election : elections) {
    std::cout << election.name << " was elected president of "
              << election.country << " in " << election.year << std::endl;
  }

  for (President const& election : reElections) {
    std::cout << election.name << " was re-elected president of "
              << election.country << " in " << election.year << std::endl;
  }

  return 0;
}