#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <boost/program_options.hpp>

void GetUsage() {
  std::cout << "Hello World!";
}

void GetContact(std::string& fname, std::string& lname, std::string& phone,
                std::string& email, std::string& birthday) {
  std::cout << "Enter first name: " << std::endl;
  std::cin >> fname;
  std::cout << "Enter last name: " << std::endl;
  std::cin >> lname;
  std::cout << "Enter phone: " << std::endl;
  std::cin >> phone;
  std::cout << "Enter email: " << std::endl;
  std::cin >> email;
  std::cout << "Enter birthday: " << std::endl;
  std::cin >> birthday;
}

void ProcessCommandLine(int argc, char* argv[]) {
  namespace po = boost::program_options;

	po::options_description generalOptions("General options");
  generalOptions.add_options()
    ("help,h", "Show help")
    ("show,s", "")
    ("new,n", "")
    ("add,a", "")
    ;

  std::vector<std::string> filters;
  po::options_description showOptions("Show options");
  showOptions.add_options()
    ("filter,f", po::value<std::vector<std::string>>(&filters), "")
    ;

  std::string fname;
  std::string lname;
  std::string phone;
  std::string email;
  std::string birthday;
  po::options_description addOptions("Add options");
  addOptions.add_options()
    ("fname,F", po::value<std::string>(&fname)->required(), "")
    ("lname,L", po::value<std::string>(&lname)->required(), "")
    ("phone,P", po::value<std::string>(&phone)->required(), "")
    ("email,E", po::value<std::string>(&email)->required(), "")
    ("birthday,B", po::value<std::string>(&birthday)->required(), "")
    ;

  const auto parse = [&argc, &argv](po::options_description& opts) {
    po::variables_map ret;
    po::parsed_options parsed = po::command_line_parser(argc, argv).options(opts).allow_unregistered().run();
    po::store(parsed, ret);
    po::notify(ret);
    return ret;
  };

  const auto vm = parse(generalOptions);
  if (vm.count("show")) {
    parse(showOptions);
  } else if (vm.count("add")) {
    parse(addOptions);
  } else if (vm.count("new")) {
    GetContact(fname, lname, phone, email, birthday);
  } else {
    GetUsage();
  }
}

int main(int argc, char* argv[]) {
  ProcessCommandLine(argc, argv);

  return 0;
}
