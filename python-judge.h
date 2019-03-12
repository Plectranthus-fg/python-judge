#include <string>

#ifndef filename
#define filename "test.py"
#endif


class arg_t {
public:
  double timelimit;
  std::string key;
};

class feedback_t {
public:
  bool compile_pass;
  bool out_of_time;
  bool result_pass;
  };
