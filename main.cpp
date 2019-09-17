#include <iostream>
using namespace std;

/*
References
https://articles.emptycrate.com/2009/02/03/overloading__op_and_operators_in_c.html
https://www.artima.com/cppsource/safebool.html
https://en.cppreference.com/w/cpp/language/operator_logical
https://en.cppreference.com/w/cpp/language/implicit_conversion
https://stackoverflow.com/questions/47031244/alias-for-a-lambda
*/

// ----------------------------------------------------------------------------

struct status{

private:

    int value;

public:

    status(int v){ value = v; }

    bool running () { return value ==  0; }
    bool failing () { return value == -1; }
    bool done    () { return value ==  1; }

    status operator!() const { return status(-value); }

    status op_and (function<status()> rhs){ return value==-1 ? value : rhs(); }

    status op_or  (function<status()> rhs){ return value==+1 ? value : rhs(); }

    char symbol(){
        switch(value){
            case -1: return 'F';
            case  0: return 'R';
            case +1: return 'D';
            default: return '?';
        }
    }

}

// ----------------------------------------------------------------------------

// Non standard, requires -fno-operator-names
// #define and(x) .xnd([=]{ return (x);})
// #define or(x) .xr([=]{ return (x);})

// // greek
#define ε(x)  .op_and ([=]{ return (x); })
#define α(x)  .op_or  ([=]{ return (x); })

// latin forms
#define et(x) .op_and ([=]{ return (x); })
#define an(x) .op_or  ([=]{ return (x); })

status seq0(status& x, status& y){
    return (x) et (y) an (x);
}

status seq1(status& x, status& y){
    return (x) ε (y) α (x);
}

status seq2(status& x, status& y){
    return status(0).op_and( [=]{ return y; } );
}

status seq3(status& x, status& y){
    return status(0).op_and( [=]{ return y; } );
}

int main(){
    auto x = status(0);
    auto y = status(1);
    status s = seq0(x, y);
    cout << "The output: " << s.symbol() << endl;
}
