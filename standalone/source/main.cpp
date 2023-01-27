#include <greeter/greeter.h>
#include <greeter/version.h>

#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <MMCore.h>

auto main(int argc, char** argv) -> int {
  const std::unordered_map<std::string, greeter::LanguageCode> languages{
      {"en", greeter::LanguageCode::EN},
      {"de", greeter::LanguageCode::DE},
      {"es", greeter::LanguageCode::ES},
      {"fr", greeter::LanguageCode::FR},
  };

  cxxopts::Options options(*argv, "A program to welcome the world!");

  std::string language;
  std::string name;

  CMMCore *mmc = new CMMCore();
  std::cout << "Core version: " << mmc->getAPIVersionInfo() << std::endl;
  std::string mdir = "/Users/talley/Library/Application Support/pymmcore-plus/mm/Micro-Manager-2.0.1-20230118";
  mmc->setDeviceAdapterSearchPaths({mdir});
  std::cout << "patjhs: " << mmc->getDeviceAdapterSearchPaths()[0] << std::endl;
  mmc->loadSystemConfiguration("/Users/talley/Desktop/MMConfig_demo.cfg");
  std::cout << "Loaded config" << std::endl;
  mmc->snapImage();
  
  std::cout << mmc->getImage() << std::endl;
  
  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("v,version", "Print the current version number")
    ("n,name", "Name to greet", cxxopts::value(name)->default_value("World"))
    ("l,lang", "Language code to use", cxxopts::value(language)->default_value("en"))
  ;
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result["help"].as<bool>()) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  if (result["version"].as<bool>()) {
    std::cout << "Greeter, version " << GREETER_VERSION << std::endl;
    return 0;
  }

  auto langIt = languages.find(language);
  if (langIt == languages.end()) {
    std::cerr << "unknown language code: " << language << std::endl;
    return 1;
  }

  greeter::Greeter greeter(name);
  std::cout << greeter.greet(langIt->second) << std::endl;

  return 0;
}
