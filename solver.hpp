#include <stdio.h>
#include <iostream>
#include "math.h"
#include <complex>

using namespace std;

namespace solver{

    class RealVariable {
    public:
        double real;

        RealVariable() {}
        ~RealVariable() {}

        class RealPolinom{     //FORM: ar^2+br+c
        private:
            double a,b,c;
            RealVariable* r;
            bool var;

        public:
            RealPolinom() : a(0), b(0), c(0), var(false){}            //default Constructor
            RealPolinom(int c) : a(0), b(0), c(c), var(false){}
            RealPolinom(double c) : a(0), b(0), c(c), var(false){}
            RealPolinom(RealVariable& r) : a(0), r(&r), b(1), c(0), var(true){}     //holds the x Final Resault into LINE
            RealPolinom(double a, double b, double c) : a(a), b(b), c(c), var(false) {}   //copy Constructor
            ~RealPolinom(){}

            double getA() { return a; };
            double getB() { return b; };
            double getC() { return c; };
            RealVariable* getX() { return r; };
            void setX(RealVariable* R) { this->r = R; }
            bool haveVar() {return this->var;}
            void setVar(bool var) { this->var = var; }
        };
        friend RealPolinom operator ^ (RealPolinom A, int e);
        friend RealPolinom operator + (RealPolinom A, RealPolinom B);
        friend RealPolinom operator - (RealPolinom A, RealPolinom B);
        friend RealPolinom operator * (RealPolinom A, RealPolinom B);
        friend RealPolinom operator / (RealPolinom A, RealPolinom B);
        friend RealPolinom operator == (RealPolinom A, RealPolinom B);
    };




//------------------------------------------------------------------------------------------------------------------------

    class ComplexVariable {
    public:
        complex<double> img;

        ComplexVariable() {}
        ~ComplexVariable() {
        }

        class ComplexPolinom{     //FORM: ax^2+bx+c
        private:
            complex<double> a,b,c;
            ComplexVariable* x;
            bool var;

        public:
            ComplexPolinom(): a(0), b(0), c(0), var(false){}            //default Constructor
            ComplexPolinom(int c) : a(0), b(0), c(c), var(false){}
            ComplexPolinom(double c) : a(0), b(0), c(c), var(false){}
            ComplexPolinom(complex<double> c) : a(0), b(0), c(c), var(false){}
            ComplexPolinom(ComplexVariable& x) : a(0), x(&x), b(1), c(0), var(true) {}     //holds the x Final Resault into LINE
            ComplexPolinom(complex<double> a, complex<double> b, complex<double> c) : a(a), b(b), c(c), var(false) {}   //copy Constructor
            ~ComplexPolinom(){}

            complex<double> getA() { return a; };
            complex<double> getB() { return b; };
            complex<double> getC() { return c; };
            ComplexVariable* getX() { return x; };
            void setX(ComplexVariable* X) { this->x = X; }
            bool haveVar() {return this->var;}
        };
        friend ComplexPolinom operator ^ (ComplexPolinom A, int e);
        friend ComplexPolinom operator + (ComplexPolinom A, ComplexPolinom B);
        friend ComplexPolinom operator - (ComplexPolinom A, ComplexPolinom B);
        friend ComplexPolinom operator * (ComplexPolinom A, ComplexPolinom B);
        friend ComplexPolinom operator / (ComplexPolinom A, ComplexPolinom B);
        friend ComplexPolinom operator == (ComplexPolinom A, ComplexPolinom B);
    };

    double solve(RealVariable::RealPolinom r);
    complex<double> solve(ComplexVariable::ComplexPolinom x);
}