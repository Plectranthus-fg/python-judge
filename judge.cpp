#include <python3.6m/Python.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

#define filename "test.py"

int main(int argc, char const *argv[]) {
  char resultname[] = "/tmp/fileXXXXXX";
  auto fd = mkstemp(resultname);
  freopen(resultname, "a", stdout);

  auto pyfile = fopen(filename, "r");
  if (!pyfile) {
    std::cerr << "Fail to open " << filename <<std::endl;
  }
  Py_Initialize();
  PyRun_SimpleFile(pyfile, filename);
  Py_Finalize();
  fclose(stdout);
  std::string resultstring;
  char buf;

  auto result = fopen(resultname,"r");
  while ((buf = fgetc(result)) != EOF)
    resultstring.push_back(buf);
  std::cerr << resultstring <<std::endl;
  return 0;
}
