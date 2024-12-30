#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

vector<string> wingetPackages = {};
map<string, string> curlLinks;
string pathToTempInstallers = "C:\\Users\\orriginalo\\AppData\\Local\\Temp\\autoInstallerPkgs";

// Pototypes:
void createDirIfNotExists(string dir);
void askForInstallPackage(string packageName, string packageId, string type);
void printStat();
void installPackages();
void askPackages();

void createDirIfNotExists(string dir) {
  if (!dir.empty()) {
    if (!fs::exists(dir)) {
      fs::create_directory(dir);
    }
  }
}

void askForInstallPackage(string packageId, string packageName, string type) {
  if (type == "winget") {
    cout << "Install " << packageName << "? [y/n]: ";
    string answer;
    cin >> answer;
    bool isInstall = answer == "y";
    if (isInstall) {
      wingetPackages.push_back(packageId);
    }
  } else if (type == "curl") {
    cout << "Install " << packageName << "? [y/n]: ";
    string answer;
    cin >> answer;
    bool isInstall = answer == "y";
    if (isInstall) {
      curlLinks[packageName] = packageId;
    }
  }
}

void printStat() {
  cout << endl;
  cout << "=============================" << endl;
  cout << "Total packages: " << wingetPackages.size() + curlLinks.size() << endl;
  cout << "-----------------------------" << endl;
  cout << "Winget packages: " << wingetPackages.size() << endl;
  cout << "Curl packages: " << curlLinks.size() << endl;
  cout << "=============================" << endl;
  cout << endl;
}

void installPackages() {

  if (wingetPackages.size() > 0) {
    cout << "------ Installing packages with winget ------" << endl;
    stringstream ss;
    for (const auto &packageId : wingetPackages) {
      ss << " " << packageId;
    }
    string totalPackagesWinget = ss.str();
    // cout << "Installing" << totalPackagesWinget << " packages... " << endl;
    // cout << "Command: winget install" + totalPackagesWinget << endl;
    system(("winget install" + totalPackagesWinget).c_str());
  }
  if (curlLinks.size() > 0) {
    cout << endl;
    cout << "------ Downloading packages with curl ------" << endl;
    for (const auto &pair : curlLinks) {
      cout << "Installing " << pair.first << " package... (" << pair.second << ")" << endl;
      system(("curl -L -o " + pathToTempInstallers + pair.first + "Installer" + ".exe " + pair.second).c_str());
      // cout << "Command: curl -L -o " + pathToTempInstallers + pair.first + "Installer" + ".exe " + pair.second << endl;
    }
  }
}

void askPackages() {
  cout << "------- DEVELOPMENT -------" << endl;
  askForInstallPackage("Python.Python.3.12", "Python 3.12", "winget");
  askForInstallPackage("https://github.com/git-for-windows/git/releases/download/v2.47.1.windows.1/Git-2.47.1-64-bit.exe", "Git", "curl");
  askForInstallPackage("Microsoft.VisualStudioCode", "Visual Studio Code", "winget");
  askForInstallPackage("Azul.Zulu.21.JDK", "Azul JDK 21", "winget");
  askForInstallPackage("GodotEngine.GodotEngine", "Godot Engine 4.3", "winget");
  askForInstallPackage("Microsoft.WindowsTerminal", "Windows Terminal", "winget");
  cout << endl;

  cout << "------- TOOLS -------" << endl;
  askForInstallPackage("7zip.7zip", "7zip", "winget");
  askForInstallPackage("Microsoft.PowerShell", "PowerShell 7", "winget");
  askForInstallPackage("voidtools.Everything", "Everything", "winget");
  askForInstallPackage("AntibodySoftware.WizTree", "WizTree", "winget");
  askForInstallPackage("qBittorrent.qBittorrent", "qBittorrent", "winget");
  askForInstallPackage("Gyan.FFmpeg", "FFmpeg", "winget");
  askForInstallPackage("ImageMagick.ImageMagick", "ImageMagick", "winget");
  askForInstallPackage("Audacity.Audacity", "Audacity", "winget");
  cout << endl;

  cout << "------- MEDIA -------" << endl;
  askForInstallPackage("Yandex.Music", "Yandex Music", "winget");
  askForInstallPackage("mpv.net", "MPV Player", "winget");
  askForInstallPackage("Telegram.TelegramDesktop", "Telegram", "winget");
  cout << endl;

  cout << "------- GAMES -------" << endl;
  askForInstallPackage("Valve.Steam", "Steam", "winget");
  askForInstallPackage("EpicGames.EpicGamesLauncher", "Epic Games", "winget");
  askForInstallPackage("PrismLauncher.PrismLauncher", "Prism Launcher", "winget");
  cout << endl;

  cout << "-------SYSTEM-------" << endl;
  askForInstallPackage("TechPowerUp.NVCleanstall", "NVCleanstall (Nvidia Driver Installer)", "winget");
  cout << endl;
}

void setupCurlPackages() {
  for (const auto &entry : fs::directory_iterator(pathToTempInstallers)) {
    if (entry.path().extension() == ".exe") {
      cout << "Installing " << entry.path().filename() << " package... (" << entry.path().string() << ")" << endl;
      system(("\"" + entry.path().string() + "\"").c_str());
      // cout << ("\"" + entry.path().string() + "\"") << endl;
    }
  }
}

int main() {
  pathToTempInstallers = fs::temp_directory_path().string() + "autoInstallerPkgs\\";
  createDirIfNotExists(pathToTempInstallers);
  askPackages();
  printStat();
  installPackages();

  if (curlLinks.size() > 0) {
    cout << endl;
    cout << "Setting up curl packages..." << endl;
    setupCurlPackages();
  }

  cout << endl;
  cout << "All packages installed!" << endl;
  cout << "Press ENTER to exit..." << endl;
  cin.get();
}
