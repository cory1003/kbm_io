/**
 * @file unit_test.h
 * @author Cory Barrett
 * @brief This is my (poor) attempt at recreating rough functionalty
 *        of the google test library in order to automate the 
 *        declaration as well as storing test function in array
 *        to be able to call them in a single loop without having
 *        to manually update a unit test array. This relys on global variables
 *        and has no support for maintaining test blocks between different test
 *        arrays.
 *        Sources for generating macros:
 *         https://www.ingramj.net/2014/11/unit-tests-for-c-in-two-macros/
 *         https://www.geeksforgeeks.org/__attribute__constructor-__attribute__destructor-syntaxes-c/
 *         https://stackoverflow.com/questions/2193544/how-to-print-additional-information-when-assert-fails
 *
 * @version 0.1
 * @date 2024-06-24
 * 
 * @copyright N/A
 * 
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>

typedef bool (*test_funct_t)();

typedef struct test_struct{
  test_funct_t func;
  char * test_name;
  bool pass;
} test_struct_t;

#define MAX_TESTS 20
test_struct_t test_functions[10] = {0};
int num_tests = 0;

const char BLACK[] = "\e[0;30m";
const char RED[]   = "\e[0;31m";
const char GREEN[] =  "\e[0;32m";
const char WHITE[] = "\e[0;37m";
const char RESET[] = "\x1b[0m";
// #define YEL "\e[0;33m"
// #define BLU "\e[0;34m"
// #define MAG "\e[0;35m"
// #define CYN "\e[0;36m"

uint64_t get_time(){
  struct timeval curr_time;
  gettimeofday(&curr_time, NULL);
  return curr_time.tv_sec * 1000000 + curr_time.tv_usec;
}

void add_test( test_funct_t func, char * test_name ){
  if( num_tests > MAX_TESTS ){
    printf("Failed to add test: %s. Max test lime of %d reached.\n",
     test_name, MAX_TESTS);
  }
  test_functions[num_tests].func = func;
  test_functions[num_tests].test_name = test_name;
  num_tests++;
}

void run_test( test_struct_t test_function_data){
  static int test_count = 0;
  // 4 characters wide with 1 decimal point
  printf("[%04.1f%%] Running Test: %s\n",
     (100.0*test_count++/num_tests), test_function_data.test_name );
  int64_t start_time = get_time();
  bool pass = test_function_data.pass = test_function_data.func();
  double run_time = (get_time() - start_time)*1e-6;
  printf("Total time: %f\n", run_time );
  if(pass ){
    printf("[%sPASS%s]\n", GREEN, RESET  );
  }else{
    printf("[%sFAIL%s]\n", RED, RESET  );
  }
}

/**
 * @brief macro to define a unit test and automatically
          save it to a test function array. tests return 
          bools, and take no arguments
 * 
 */
#define UNIT_TEST(test_name) \
    bool test_name(); \
    __attribute__((constructor)) void add_##test_name() { \
        add_test(test_name, #test_name); \
    } \
    bool test_name()

/**
 * @brief modified assert macro from Notinlist on stackoverflow.
 *        returns false and exits test program if assert fails
 * 
 */
#define ASSERT(condition) \
    if (!(condition)) { \
        printf("ASSERT failed: %s, \nFile: %s\
        \nLine Numer: %d\n", #condition, __FILE__, __LINE__ ); \
        return false;\
    } \
