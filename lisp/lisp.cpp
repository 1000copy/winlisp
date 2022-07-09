// 编译运行方法
// VsDevCmd.bat
// cl  user32.lib gdi32.lib wisp.cpp
// 解决DrawText输出乱码 ：save　cpp file encoded by UTF-16 LE
// 但是在IDE环境内，中文会乱码。搞不懂。
//  搞定：把IDE内的字符集默认的UNICODE改成未设置。具体修改方法：Project属性 - 高级 - 字符集 - UNICODE 选择改为 未设置
/*如果选择了“使用Unicode字符集”，则代码里用到的API被解释为Unicode版本的API（带标记W的API），如MessageBox被解释为MessageBoxW；
如果选择了“使用多字节字符集”，则代码里用到的API被解释为ANSI编码版本的API（带标记A的API），如MessageBox被解释为MessageBoxA。
*/
#include "lisp.h"
char delimiter = '\'';
char leftp = '('; //'[';
char rightp = ')';//']';
// return given mumber as a string
std::string str(long n) { std::ostringstream os; os << n; return os.str(); }

// return true iff given character is '0'..'9'
bool isdig(char c) { return isdigit(static_cast<unsigned char>(c)) != 0; }
bool isstr(char c) { return c == delimiter; }



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

cell proc_add(const cells& c)
{
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

cell proc_length(const cells& c) { return cell(Number, str(c[0].list.size())); }
cell proc_nullp(const cells& c) { return c[0].list.empty() ? true_sym : false_sym; }
cell proc_car(const cells& c) { return c[0].list[0]; }

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
        if (x.list[0].val == "quote")       // (quote exp)
            return x.list[1];
        if (x.list[0].val == "if")          // (if test conseq [alt])
            return eval(eval(x.list[1], env).val == "#f" ? (x.list.size() < 4 ? nil : x.list[3]) : x.list[2], env);
        if (x.list[0].val == "set!")        // (set! var exp)
            return env->find(x.list[1].val)[x.list[1].val] = eval(x.list[2], env);
        if (x.list[0].val == "define")      // (define var exp)
            return (*env)[x.list[1].val] = eval(x.list[2], env);
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
    }
    // (proc exp*)
    cell proc(eval(x.list[0], env));
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
        return eval(/*body*/proc.list[2], new environment(/*parms*/proc.list[1].list, /*args*/exps, proc.env));
    }
    else if (proc.type == Proc)
        return proc.proc(exps);

    std::cout << "not a function\n";
    exit(1);
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
            while (*t && *t != delimiter)
                ++t;
            tokens.push_back(std::string(s, t + 1));
            s = t + 1;
        }
        else {
            const char* t = s;
            while (*t && *t != ' ' && *t != leftp && *t != rightp)
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


/*------------------------------------------------------------
   HELLOWIN.C -- Displays "Hello, Windows 98!" in client area
                 (c) Charles Petzold, 1998
  ------------------------------------------------------------*/


