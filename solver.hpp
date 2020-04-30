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
    };

    class ComplexVariable {
    public:
        complex<double> img;

        ComplexVariable() {}
        ~ComplexVariable() {}
    };

    class polinom{     //FORM: ar^e+br+c
    private:
        double a,b,c;
        RealVariable* r;
        bool var;

    public:
        polinom() : a(0), b(0), c(0), var(false){}            //default Constructor
        polinom(int c) : a(0), b(0), c(c), var(false){}
        polinom(double c) : a(0), b(0), c(c), var(false){}
        polinom(RealVariable& r) : a(0), r(&r), b(1), c(0), var(true){}     //holds the x Final Resault into LINE
        polinom(double a, double b, double c) : a(a), b(b), c(c), var(false) {}   //copy Constructor
//        ~POLI(){}

        double getA() { return a; };
        double getB() { return b; };
        double getC() { return c; };
        RealVariable* getX() { return r; };
        void setX(RealVariable* R) { this->r = R; }
        bool haveVar() {return this->var;}
    };



//------------------------------------------------------------------------------------------------------------------------

    class complexPolinom{     //FORM: ax^e+bx+c
    private:
        complex<double> a,b,c;
        ComplexVariable* x;
        bool var;

    public:
        complexPolinom(): a(0), b(0), c(0), var(false){}            //default Constructor
        complexPolinom(int c) : a(0), b(0), c(c), var(false){}
        complexPolinom(double c) : a(0), b(0), c(c), var(false){}
        complexPolinom(complex<double> c) : a(0), b(0), c(c), var(false){}
        complexPolinom(ComplexVariable& x) : a(0), x(&x), b(1), c(0), var(true) {}     //holds the x Final Resault into LINE
        complexPolinom(complex<double> a, complex<double> b, complex<double> c) : a(a), b(b), c(c), var(false) {}   //copy Constructor
        ~complexPolinom(){}

        complex<double> getA() { return a; };
        complex<double> getB() { return b; };
        complex<double> getC() { return c; };
        ComplexVariable* getX() { return x; };
        void setX(ComplexVariable* X) { this->x = X; }
        bool haveVar() {return this->var;}
    };

//------------------------------------------------------------------------------------------------------------------------

    polinom operator ^ (polinom A, int e){
        polinom R( A.getB(),0, A.getC());
        R.setX(A.getX());
        return R;
    }

    polinom operator + (polinom A, polinom B){
        polinom R(A.getA()+B.getA(), A.getB()+B.getB(), A.getC()+B.getC());
        if(A.getX()) R.setX(A.getX());
        else R.setX(B.getX());
        return R;
    }

    polinom operator - (polinom A, polinom B){
        polinom R(A.getA()-B.getA(), A.getB()-B.getB(), A.getC()-B.getC());
        if(A.getX()) R.setX(A.getX());
        else R.setX(B.getX());
        return R;
    }

    polinom operator * (polinom A, polinom B){  // b1r+c1 * b2r+c2
        polinom R(0,(A.getC()*B.getB())+(B.getC()*A.getB()), A.getC()*B.getC());
        if (A.haveVar()) R.setX(A.getX());
        else R.setX(B.getX());
        return R;
    }

    polinom operator / (polinom A, polinom B){ //  b1*r+c1 / b2*r+c2   ->   (b1/b2)*r+(c1/c2)
        if (B.getC() == 0 && B.getB()==0 && B.getA()==0) throw runtime_error("can not divide by 0!!");
        if (B.getC() == 0 && B.getB()==0) return A;
        if (B.getC() == 0) {
            polinom R(0, 0, A.getB() / B.getB());
            R.setX(A.getX());
            return R;
        }
        polinom R(0, A.getB() / B.getC(), A.getC() / B.getC());
        R.setX(A.getX());
        return R;
    }

    polinom operator == (polinom A, polinom B){
        polinom C = A - B;
        if (C.getA()==0 && C.getB()==0) {
            if (C.getC()==0){
                C.getX()->real=0;
                return C;
            }
            else throw runtime_error("there is no solution");
        }
        if (C.getA()==0) C.getX()->real = -C.getC()/C.getB();
        else {
            double x = (-C.getB() + sqrtf(powf(C.getB(), 2) - (4*C.getA()*C.getC())))/(2*C.getA());
            if (isnan(x)) throw runtime_error("there is no solution");
            C.getX()->real = x;
        }
        return C;
    }



//------------------------------------------------------------------------------------------------------------------------



    complexPolinom operator ^ (complexPolinom A, int e){
        complexPolinom R(A.getB(), 0, A.getC());
        R.setX(A.getX());
        return R;
    }

    complexPolinom operator + (complexPolinom A, complexPolinom B){
        complexPolinom R(A.getA() + B.getA(), A.getB() + B.getB(), A.getC() + B.getC());
        if(A.getX()) R.setX(A.getX());
        else R.setX(B.getX());
        return R;
    }

    complexPolinom operator - (complexPolinom A, complexPolinom B){
        complexPolinom R(A.getA() - B.getA(), A.getB() - B.getB(), A.getC() - B.getC());
        if(A.getX()) R.setX(A.getX());
        else R.setX(B.getX());
        return R;
    }

    complexPolinom operator * (complexPolinom A, complexPolinom B){
        complexPolinom R(0, (A.getC() * B.getB()) + (B.getC() * A.getB()), A.getC() * B.getC());
        if (A.haveVar()) R.setX(A.getX());
        else R.setX(B.getX());
        return R;
    }

    complexPolinom operator / (complexPolinom A, complexPolinom B){
        complex<double> zero=0;
        if (B.getC() == zero ) return A;
        complexPolinom R(0, A.getB() / B.getC(), A.getC() / B.getC());
        R.setX(A.getX());
        return R;
    }

    complexPolinom operator == (complexPolinom A, complexPolinom B){
        complexPolinom C = A - B;
        complex<double> zero=0, two = 2, four = 4;
        if (C.getA()==zero) C.getX()->img = -C.getC()/C.getB();
        else C.getX()->img = (-C.getB() + sqrt(pow(C.getB(), two) - (four*C.getA()*C.getC())))/(two*C.getA());
        return C;
    }

    double solve(polinom r){return r.getX()->real;}
    complex<double> solve(complexPolinom x){return x.getX()->img;}

}

