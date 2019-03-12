#include <fstream>
#include <iostream>
#include <python3.6m/Python.h>
#include <string>
#include <time.h>
#include <unistd.h>
#include <vector>
#include "python-judge.h"


feedback_t python_judge(arg_t argument) {
  feedback_t feedback;
  double uptime;
  clock_t start, end;
  char resultname[] = "/tmp/fileXXXXXX";
  auto fd = mkstemp(resultname);
  freopen(resultname, "a", stdout);
  auto pyfile = fopen(filename, "r");
  if (!pyfile) {
    std::cerr << "Fail to open " << filename << std::endl;
  }

  Py_Initialize();

  start = clock();
  PyRun_SimpleFile(pyfile, filename);
  end = clock();

  Py_Finalize();
  fclose(stdout);

  //答案存入resultstring中以供检查
  std::string resultstring;
  char buf;
  auto result = fopen(resultname, "r");
  while ((buf = fgetc(result)) != EOF) {
    resultstring.push_back(buf);
  }
  uptime = double((end - start)) / CLOCKS_PER_SEC;
  //std::cerr << resultstring <<std::endl;
  //std::cerr << uptime << std::endl;

  if (uptime > argument.timelimit)
    feedback.out_of_time = true;
  if (resultstring == argument.key)
    feedback.result_pass = true;
  if (resultstring.c_str() == nullptr)
    feedback.compile_pass =false;

  unlink(resultname);
  return feedback;
}

// int main(){
//   arg_t arg{
//     .timelimit = 0.1,
//     .key = "yes"
//   };
//   std::cerr  << python_judge(arg).out_of_time <<std::endl;
//   return 0;
// }