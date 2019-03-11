#include "python/Python.h"

int main(int argc, char const *argv[]) {
  Py_Initalize();
  PyRun_SimpleString("print('Hello word')\n");
  Py_Finalize();
  return 0;
}
