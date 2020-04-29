#include <stdio.h>
#include <iostream>
#include <complex>
#include "math.h"

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

//------------------------------------------------------------------------------------------------------------------------

    class POLI{     //FORM: ar^e+br+c
    private:
        double a,b,c;
        int e;
        RealVariable* r;

    public:
        POLI() : a(0), b(0), c(0), e(1){}            //default Constructor
        POLI(int c) : a(0), b(0), c(c), e(1){}
        POLI(double c) : a(0), b(0), c(c), e(1){}
        POLI(RealVariable& r) : a(1), r(&r), b(0), c(0) {}     //holds the x Final Resault into LINE
        POLI(double a, int e) : a(a), e(e) {}        //make form of: x^e into POLI
        POLI(double a, double b, double c, int e) : a(a), b(b), c(c), e(e) {}   //copy Constructor
        ~POLI(){}

        double getA() { return a; };
        double getB() { return b; };
        double getC() { return c; };
        int getE() { return e; };
        RealVariable* getX() { return r; };
        void setX(RealVariable* R) { this->r = R; }
    };



//------------------------------------------------------------------------------------------------------------------------


    POLI operator ^ (POLI A, int e){
//        POLI R(0, A.getB(), A.getC(), A.getE()*e);
//        R.setX(A.getX());
//        return R;
        POLI t(5);
        t.setX(A.getX());
        t.getX()->real = 5;
        return t;
    }

    POLI operator + (POLI A, POLI B){
//        POLI R(A.getA()+B.getA(), A.getB()+B.getB(), A.getC()+B.getC(), A.getE());
//        R.setX(A.getX());
//        return R;
        POLI t(5);
        t.setX(A.getX());
        t.getX()->real = 5;
        return t;
    }

    POLI operator - (POLI A, POLI B){
//        POLI R(A.getA()-B.getA(), A.getB()-B.getB(), A.getC()-B.getC(), A.getE());
//        R.setX(A.getX());
//        return R;
        POLI t(5);
        t.setX(A.getX());
        t.getX()->real = 5;
        return t;
    }

    POLI operator * (POLI A, POLI B){
////        POLI R(A.getA()*B.getB()+B.getA()*A.getB(), A.getB()*B.getB());
////        if (A.getX()) R.setX(A.getX());
////        else R.setX(B.getX());
////        return R;
//        POLI R(A.getA()+B.getA(), A.getB()+B.getB(), A.getC()+B.getC(), A.getE());
//        R.setX(A.getX());
//        return R;
        POLI t(5);
        t.setX(A.getX());
        t.getX()->real = 5;
        return t;
    }

    POLI operator / (POLI A, POLI B){
////        POLI R(A.getA()/B.getB(), A.getB()/B.getB());
////        R.setX(A.getX());
////        return R;
//        POLI R(A.getA()-B.getA(), A.getB()-B.getB(), A.getC()-B.getC(), A.getE());
//        R.setX(A.getX());
//        return R;
        POLI t(5);
        t.setX(A.getX());
        t.getX()->real = 5;
        return t;
    }

    POLI operator == (POLI A, POLI B){
//        POLI C = A - B;
//        C.getX()->real = (-C.getB() + sqrtf(powf(C.getB(), 2) - (4*C.getA()*C.getC())))/(2*C.getA());
//        return C;
        POLI t(5);
        t.setX(A.getX());
        t.getX()->real = 5;
        return t;
    }



//------------------------------------------------------------------------------------------------------------------------


    class POLIcx{     //FORM: ax^e+bx+c
    private:
        complex<double> a,b,c;
        int e;
        ComplexVariable* x;

    public:
        POLIcx(): a(0), b(0), c(0), e(1){}            //default Constructor
        POLIcx(int c) : a(0), b(0), c(c), e(1){}
        POLIcx(double c) : a(0), b(0), c(c), e(1){}
        POLIcx(complex<double> c) : a(0), b(0), c(c), e(1){}
        POLIcx(ComplexVariable& x) : a(1), x(&x), b(0), c(0) {}     //holds the x Final Resault into LINE
        POLIcx(complex<double> a, int e) : a(a), e(e) {}        //make form of: x^e into POLI
        POLIcx(complex<double> a, complex<double> b, complex<double> c, int e) : a(a), b(b), c(c), e(e) {}   //copy Constructor
        ~POLIcx(){}

        complex<double> getA() { return a; };
        complex<double> getB() { return b; };
        complex<double> getC() { return c; };
        int getE() { return e; };
        ComplexVariable* getX() { return x; };
        void setX(ComplexVariable* X) { this->x = X; }
    };


//------------------------------------------------------------------------------------------------------------------------


    POLIcx operator ^ (POLIcx A, int e){
//        POLIcx R(0, A.getB(), A.getC(), e);
//        R.setX(A.getX());
//        return R;
        POLIcx t(5);
        t.setX(A.getX());
        t.getX()->img = 5;
        return t;
    }

    POLIcx operator + (POLIcx A, POLIcx B){
//        POLIcx R(A.getA()+B.getA(), A.getB()+B.getB(), A.getC()+B.getC(), A.getE());
//        R.setX(A.getX());
//        return R;
        POLIcx t(5);
        t.setX(A.getX());
        t.getX()->img = 5;
        return t;
    }

    POLIcx operator - (POLIcx A, POLIcx B){
//        POLIcx R(A.getA()-B.getA(), A.getB()-B.getB(), A.getC()-B.getC(), A.getE());
//        R.setX(A.getX());
//        return R;
        POLIcx t(5);
        t.setX(A.getX());
        t.getX()->img = 5;
        return t;
    }

    POLIcx operator * (POLIcx A, POLIcx B){
////        POLI R(A.getA()*B.getB()+B.getA()*A.getB(), A.getB()*B.getB());
////        if (A.getX()) R.setX(A.getX());
////        else R.setX(B.getX());
////        return R;
//        POLIcx R(A.getA()+B.getA(), A.getB()+B.getB(), A.getC()+B.getC(), A.getE());
//        R.setX(A.getX());
//        return R;
        POLIcx t(5);
        t.setX(A.getX());
        t.getX()->img = 5;
        return t;
    }

    POLIcx operator / (POLIcx A, POLIcx B){
////        POLI R(A.getA()/B.getB(), A.getB()/B.getB());
////        R.setX(A.getX());
////        return R;
//        POLIcx R(A.getA()-B.getA(), A.getB()-B.getB(), A.getC()-B.getC(), A.getE());
//        R.setX(A.getX());
//        return R;
        POLIcx t(5);
        t.setX(A.getX());
        t.getX()->img = 5;
        return t;
    }

    POLIcx operator == (POLIcx A, POLIcx B){
//        POLIcx C = A - B;
//        C.getX()->img = (-C.getB() + sqrt(pow(C.getB(), 2) - (C.getA()*C.getC())))/(C.getA());
//        return C;
        POLIcx t(5);
        t.setX(A.getX());
        t.getX()->img = 5;
        return t;
    }


//------------------------------------------------------------------------------------------------------------------------

    double solve(POLI r){return r.getX()->real;}
    complex<double> solve(POLIcx x){return x.getX()->img;}


}

