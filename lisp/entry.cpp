#include "lisp.h"
environment global_env;

// the default read-eval-print-loop
void repl(const std::string& prompt, environment* env)
{
    for (;;) {
        std::cout << prompt;
        std::string line; std::getline(std::cin, line);
        std::cout << to_string(eval(read(line), env)) << '\n';
    }
}

int main()
{
    environment global_env; add_globals(global_env);
    repl("90> ", &global_env);
}


//
//int main()
//{
//    environment global_env; add_globals(global_env);
//    //std::cout << to_string(eval(read("(+ 1 3)"), &global_env)) << '\n';
//    //std::cout << to_string(eval(read("(quote(one \ntwo))"), &global_env)) << '\n';
//    //std::cout << to_string(eval(read("(car(quote(one \ntwo)))"), &global_env)) << '\n';
//    //std::cout << to_string(eval(read("'ok'"), &global_env)) << '\n';
//    //std::cout << to_string(eval(read("[cat 'ok' '3']"), &global_env)) << '\n';
//    // std::cout << to_string(eval(read("(cat 'ok' '2' '4')"), &global_env)) << '\n';
//    // std::cout << to_string(eval(read("(cat 'prefix' (cat 'ok' '2' '4'))"), &global_env)) << '\n';
//    //(begin(define a '1')(set! a '2')))
//    repl("90> ", &global_env);
//}
