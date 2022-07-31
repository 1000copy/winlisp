
#include <fstream>

#include "lisp.h"
char delimiter = '\'';
char delimiter1 = '"';
char leftp = '('; //'[';
char rightp = ')';//']';
// return given mumber as a string
std::string str(long n) { std::ostringstream os; os << n; return os.str(); }

// return true iff given character is '0'..'9'
bool isdig(char c) { return isdigit(static_cast<unsigned char>(c)) != 0; }
bool isstr(char c) { return c == delimiter || c==delimiter1; }



////////////////////// built-in primitive procedures


cell proc_cat(const cells& c)
{
    std::string base(c[0].val.c_str());
    for (cellit i = c.begin() + 1; i != c.end(); ++i) base += i->val.c_str();
    return cell(String, base);
}
cell proc_p(const cells& c)
{
    // std::cout << "dkdkdk";
    // std::string base(c[0].val.c_str());
    for (cellit i = c.begin() ; i != c.end(); ++i) std::cout<< i->val.c_str() << " ";
    std::cout << "\n";
    return true_sym;
}
void log(std::string str){
    std::cout<< str << "\n`";
}
cell proc_add(const cells& c)
{
    // log("+ proc");
    long n(atol(c[0].val.c_str()));
    for (cellit i = c.begin() + 1; i != c.end(); ++i) n += atol(i->val.c_str());
    return cell(Number, str(n));
}
cell proc_equal(const cells& c)
{
    bool b = true;
    long n(atol(c[0].val.c_str()));
    for (cellit i = c.begin() + 1; i != c.end(); ++i) b &=  n == atol(i->val.c_str());
    if (b)
        return true_sym;
    else
        return false_sym;
    //return cell(Number, str(n));
}

cell proc_sub(const cells& c)
{
    long n(atol(c[0].val.c_str()));
    for (cellit i = c.begin() + 1; i != c.end(); ++i) n -= atol(i->val.c_str());
    return cell(Number, str(n));
}

cell proc_mul(const cells& c)
{
    long n(1);
    for (cellit i = c.begin(); i != c.end(); ++i) n *= atol(i->val.c_str());
    return cell(Number, str(n));
}

cell proc_div(const cells& c)
{
    long n(atol(c[0].val.c_str()));
    for (cellit i = c.begin() + 1; i != c.end(); ++i) n /= atol(i->val.c_str());
    return cell(Number, str(n));
}

cell proc_greater(const cells& c)
{
    long n(atol(c[0].val.c_str()));
    for (cellit i = c.begin() + 1; i != c.end(); ++i)
        if (n <= atol(i->val.c_str()))
            return false_sym;
    return true_sym;
}

cell proc_less(const cells& c)
{
    long n(atol(c[0].val.c_str()));
    for (cellit i = c.begin() + 1; i != c.end(); ++i)
        if (n >= atol(i->val.c_str()))
            return false_sym;
    return true_sym;
}

cell proc_less_equal(const cells& c)
{
    long n(atol(c[0].val.c_str()));
    for (cellit i = c.begin() + 1; i != c.end(); ++i)
        if (n > atol(i->val.c_str()))
            return false_sym;
    return true_sym;
}

cell proc_length(const cells& c) { 
    std::stringstream ss;
    ss << c[0].list.size();
    return cell(Number, ss.str()); 
}
cell proc_nullp(const cells& c) { return c[0].list.empty() ? true_sym : false_sym; }
cell proc_car(const cells& c) { return c[0].list[0]; }
cell proc_nth(const cells& c) { 
    int i = atoi(c[1].val.c_str());
    return c[0].list[i]; }
cell proc_cdr(const cells& c)
{
    if (c[0].list.size() < 2)
        return nil;
    cell result(c[0]);
    result.list.erase(result.list.begin());
    return result;
}

cell proc_append(const cells& c)
{
    cell result(List);
    result.list = c[0].list;
    for (cellit i = c[1].list.begin(); i != c[1].list.end(); ++i) result.list.push_back(*i);
    return result;
}

cell proc_cons(const cells& c)
{
    cell result(List);
    result.list.push_back(c[0]);
    for (cellit i = c[1].list.begin(); i != c[1].list.end(); ++i) result.list.push_back(*i);
    return result;
}

cell proc_list(const cells& c)
{
    cell result(List); result.list = c;
    return result;
}


// define the bare minimum set of primintives necessary to pass the unit tests
void add_globals(environment& env)
{
    env["nil"] = nil;   env["#f"] = false_sym;  env["#t"] = true_sym;
    env["append"] = cell(&proc_append);   env["car"] = cell(&proc_car);
    env["cdr"] = cell(&proc_cdr);      env["cons"] = cell(&proc_cons);
    env["length"] = cell(&proc_length);   env["list"] = cell(&proc_list);
    env["null?"] = cell(&proc_nullp);    env["+"] = cell(&proc_add);
    env["="] = cell(&proc_equal);
    env["-"] = cell(&proc_sub);      env["*"] = cell(&proc_mul);
    env["/"] = cell(&proc_div);      env[">"] = cell(&proc_greater);
    env["<"] = cell(&proc_less);     env["<="] = cell(&proc_less_equal);
    env["cat"] = cell(&proc_cat);
    env["p"] = cell(&proc_p);     
    env["nth"] = cell(&proc_nth);
}

////////////////////// eval
cell run(std::string str, environment* env) {
        return eval(read(str), env);
    
}
cell eval(cell x, environment* env)
{
    if (x.type == Symbol)
        return env->find(x.val)[x.val];
    if (x.type == Number)
        return x;
    if (x.type == String)
        return x;
    if (x.list.empty())
        return nil;
    if (x.list[0].type == Symbol) {
        //log("eval list:"); log(x.list[0].val);
        if (x.list[0].val == "quote")       // (quote exp)
            return x.list[1];
        if (x.list[0].val == "if")          // (if test conseq [alt])
            return eval(eval(x.list[1], env).val == "#f" ? (x.list.size() < 4 ? nil : x.list[3]) : x.list[2], env);
        if (x.list[0].val == "set!") {        // (set! var exp)
            size_t count = (x.list.size() - 1) / 2;
            for (int i = 0; i < count; i++) {
                cell a = eval(x.list[2 * i + 2], env);
                env->find(x.list[2 * i + 1].val)[x.list[2 * i + 1].val] = a;
                if (i == count - 1)
                    return a;
            }
        }
        if (x.list[0].val == "define" || x.list[0].val == "def") {      // (define var exp)
            size_t count = (x.list.size()-1) / 2;
            for (int i = 0; i < count ; i++) {
                cell a = eval(x.list[2*i+2], env);
                (*env)[x.list[2 * i + 1].val] = a;
                if (i == count - 1)
                    return a;
            }
        }
        if (x.list[0].val == "define!" || x.list[0].val == "def!") {      // (define var exp)
            size_t count = (x.list.size() - 1) / 2;
            for (int i = 0; i < count; i++) {
                cell a = x.list[2 * i + 2];
                (*env)[x.list[2 * i + 1].val] = a;
                if (i == count - 1)return a;
            }
        }
        if (x.list[0].val == "lambda") {    // (lambda (var*) exp)
            x.type = Lambda;
            // keep a reference to the environment that exists now (when the
            // lambda is being defined) because that's the outer environment
            // we'll need to use when the lambda is executed
            x.env = env;
            return x;
        }
        if (x.list[0].val == "begin") {     // (begin exp*)
            for (size_t i = 1; i < x.list.size() - 1; ++i)
                eval(x.list[i], env);
            return eval(x.list[x.list.size() - 1], env);
        }
        if (x.list[0].val == "repeat") {     // (repeat exp exp)
            cell count = eval(x.list[1], env);
            long cc = atol(count.val.c_str());
            for (size_t i = 1; i < cc; ++i)
                eval(x.list[2], env);
            return eval(x.list[2], env);
        }
    }
    // (proc exp*)
    //log("eval proc:");
    cell proc(eval(x.list[0], env));
    //ofstream myFile_Handler;
    //myFile_Handler.open("log.txt", std::ios_base::app);
    //myFile_Handler << x.list[0].val << endl;
    //myFile_Handler.close();
    cells exps;
    for (cell::iter exp = x.list.begin() + 1; exp != x.list.end(); ++exp)
        exps.push_back(eval(*exp, env));
    if (proc.type == Lambda) {
        // Create an environment for the execution of this lambda function
        // where the outer environment is the one that existed* at the time
        // the lambda was defined and the new inner associations are the
        // parameter names with the given arguments.
        // *Although the environmet existed at the time the lambda was defined
        // it wasn't necessarily complete - it may have subsequently had
        // more symbols defined in that environment.
        const cells& parms = proc.list[1].list;
        const cells& args = exps;
            if (args.size() != parms.size()) {
                // std::cout << "params length must be equal to args length" << args.size() << parms.size() << "'\n";
                std::stringstream buffer;
                buffer << "lambda params :";
                buffer << to_string1(parms);
                buffer << "not match args :";
                buffer << to_string1(args);
                throw buffer.str();
            }
            return eval(/*body*/proc.list[2], new environment(parms, args, proc.env));
        
        //return eval(/*body*/proc.list[2], new environment(/*parms*/proc.list[1].list, /*args*/exps, proc.env));
    }
    else if (proc.type == Proc)
        return proc.proc(exps);
    std::stringstream buffer;
    buffer << "not a function '" << x.val << "'";
    throw buffer.str();
}


////////////////////// parse, read and user interaction

// convert given string to list of tokens
std::list<std::string> tokenize(const std::string& str)
{
    std::list<std::string> tokens;
    const char* s = str.c_str();
    while (*s) {
        while (*s == ' ' || *s == '\n')
            ++s;
        if (*s == leftp || *s == rightp)
            tokens.push_back(*s++ == leftp ? "(" : ")");
        else if (*s == delimiter) {
            const char* t = s + 1;
            while (*t && *t != delimiter && *t != delimiter1)
                ++t;
            tokens.push_back(std::string(s, t + 1));
            s = t + 1;
        }
        else {
            const char* t = s;
            while (*t && *t != ' ' && *t != '\n' && *t != leftp && *t != rightp)
                ++t;
            tokens.push_back(std::string(s, t));
            s = t;
        }
    }
    return tokens;
}

// numbers become Numbers; every other token is a Symbol
cell atom(const std::string& token)
{
    if (isdig(token[0]) || (token[0] == '-' && isdig(token[1])))
        return cell(Number, token);
    if (isstr(token[0]))
        return cell(String, token.substr(1, token.length() - 2));
    return cell(Symbol, token);
}

// return the Lisp expression in the given tokens
cell read_from(std::list<std::string>& tokens)
{
    const std::string token(tokens.front());
    tokens.pop_front();
    if (token == "(") {
        cell c(List);
        while (tokens.front() != ")")
            c.list.push_back(read_from(tokens));
        tokens.pop_front();
        return c;
    }
    else
        return atom(token);
}

// return the Lisp expression represented by the given string
cell read(const std::string& s)
{
    std::list<std::string> tokens(tokenize(s));
    return read_from(tokens);
}

// convert given cell to a Lisp-readable string
std::string to_string(const cell& exp)
{
    if (exp.type == List) {
        std::string s("(");
        for (cell::iter e = exp.list.begin(); e != exp.list.end(); ++e)
            s += to_string(*e) + ' ';
        if (s[s.size() - 1] == ' ')
            s.erase(s.size() - 1);
        return s + rightp;
    }
    else if (exp.type == Lambda)
        return "<Lambda>";
    else if (exp.type == Proc)
        return "<Proc>";
    return exp.val;
}

std::string to_string1(const cells& c)
{
    std::string s("(");
    for (cellit i = c.begin(); i != c.end(); ++i) {
        s += to_string(*i);
        s += " ";
    }
    s += ")";
    return s;
}
