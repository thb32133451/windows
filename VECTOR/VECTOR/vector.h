#ifndef _Vector
#define _Vector
#include <iostream>

namespace VECTOR {
	class Vector {
	public:
		enum MODE {RECT,POL};   // ��ʾ�������
	private:
		double x;    //������
		double y;    //������
		double mag;  //��
		double ang;  //ʸ�����򣨽Ƕ�ֵ��
		MODE mode;

		//˽�з���
		void set_mag();
		void set_ang();
		void set_x();
		void set_y();
	public:
		Vector();
		Vector(double n1,double n2,MODE form = RECT);
		void reset(double n1, double n2, MODE form = RECT);
		~Vector();

		double xval() const { return x; };
		double yval() const { return y; };
		double magval() const { return mag; };
		double angval() const { return ang; };
		void polar_mode();
		void rect_mode();

		Vector operator+(const Vector & b) const;
		Vector operator-(const Vector & b) const;
		Vector operator-() const;
		Vector operator*(double n) const;

		friend Vector operator*(double n, const Vector & a);
		friend std::ostream & operator<<(std::ostream & os, const Vector & v);
	};
}

#endif