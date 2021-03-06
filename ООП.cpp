// ���.cpp: ���������� ����� ����� ��� ����������� ����������.
//

// ��� 3.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <string.h>
//#include "Template2enk.h"
using namespace std;

extern enum typeEnk
{
	drill,      //�����
	screwdriver,   //����������
	saw,           //����
	angleGrinder, //��������
	plane,         //�������
	jigsaw,			//������
	other
};
char* GetTypeEnk(typeEnk t)
{
	switch (t)
	{
	case drill:
		return "�����";
	case screwdriver:
		return "����������";
	case saw:
		return "����";
	case angleGrinder:
		return "��������";
	case plane:
		return "�������";
	case jigsaw:
		return "������";
	default:
		return "������";
	}
}

extern enum typeFuel
{
	petrol,
	disel_fuel,
	eco
};


class enkBasis
{
private:
	int SecretIndex;
protected:
	typeEnk type;
	float mass;
	int power;
public:
	enkBasis();
	enkBasis(typeEnk t, float m, int p);
	void ShowMassAndPower();
	virtual void print();
};

class petBasis
{
private:
	int SecretIndexZ;
protected:
	typeFuel typeF;
	float mass; //��� �������� ���������������
	int stokes;
public:
	petBasis();
	petBasis(typeFuel t, float m, int p);
	void ShowMassAndStokes();
	virtual void print();
};

petBasis::petBasis()
{
	typeF = petrol;
	mass = 0;
	stokes = 0;
	SecretIndexZ = 88;
}

petBasis::petBasis(typeFuel t, float m, int p)
{
	typeF = t;
	mass = m;
	stokes = p;
	SecretIndexZ = 99;
}

void petBasis::ShowMassAndStokes()
{
	cout << endl << "Mass: " << mass << " - Stokes: " << stokes << endl;
}

void petBasis::print()
{
	if(typeF == 0)
	cout << "\n��� �������: " << "������";
	else if ((typeF == 1))
		cout << "\n��� �������: " << "���������";
	else cout << "\n��� �������: " << "���";
	
	cout << "\n�����: " << mass
		<< "\n����� ���������: " << stokes << endl;
}

class DualTool : public petBasis, public enkBasis
{
private:
	int cost;
public:
	DualTool();
	DualTool(int cost, typeFuel tf, typeEnk te, float mass, int stok,int power);
	void print();
};

DualTool::DualTool():petBasis(), enkBasis()
{
	cost = 0;
}
DualTool::DualTool(int cc, typeFuel tf, typeEnk te, float m, int stok, int power) : petBasis(tf,m ,stok), enkBasis(te,m,power)
{
	cost = cc;
}
void DualTool::print()
{
	cout << "################################";
	enkBasis::print(); petBasis::print();
	cout << "����: " << cost;
	cout << "\n################################";

}

template <class T >
class enk : public enkBasis
{
public:
	enk();//:enkBasis();
	enk(typeEnk t, char* n, T c, double m, int p);//:enkBasis( t,  m,  p);
	enk(const enk<T> &m);
	~enk();

	void input(typeEnk t, char* n, T c, double m, int p);
	void print();
	void copy(const enk<T> &x);
	enk summa(enk<T> b);
	bool sravn(enk<T> x);

	enk&  operator++() //����������
	{
		this->cost++;
		return *this;
	}
	enk&  operator--() //����������
	{
		if (cost > 0)
			this->cost--;
		return *this;
	}
	enk operator++ (int)
	{
		enk prev = *this;
		++*this;
		return prev;
	}
	enk operator--(int) //�����������
	{
		enk tmp;
		tmp = *this;
		if (cost > 0)
			this->cost--;
		return tmp;
	}
	enk&  operator = ( enk<T>& right)
	{
		if(this != &right)
		{ 
			type = right.type;
			 /*if (name != NULL) delete[] name;*/
			if (right.name != NULL)
			{
				name = new char[strlen(right.name) + 1];
				strcpy(name, right.name);
			}
			cost = right.cost;
			mass = right.mass;
			power = right.power;
		}
		return *this;
	}
	enk operator += (enk<T> m)
	{
		*this = this->summa(m);
		return *this;
	}
	enk  operator + (const enk<T> m)
	{
		return this->summa(m);
	}

	bool operator == (enk<T> x)
	{
		return (type == x.type && !strcmp(name, x.name) && cost == x.cost && mass == x.mass && power == x.power);
	}
	bool operator != ( enk<T> x)
	{
		return !(type == x.type && !strcmp(name, x.name) && cost == x.cost && mass == x.mass && power == x.power);
	}
private:

	char* name;
	T cost;
};






int main()
{
	setlocale(LC_ALL, "rus");
	enkBasis b,a= enkBasis();
	a.print();

	b = enkBasis(drill,2000,5000);
	b.print();

	petBasis z, c = petBasis();
	c.print();

	z = petBasis(eco, 2.33, 4);
	z.print();

	//�����������
	DualTool X, Y = DualTool();
	Y.ShowMassAndPower(); //����� enkBasis
	Y.ShowMassAndStokes();  //����� petBasis

	Y.print();

	X = DualTool(1500,disel_fuel,drill,2.499, 2,5000);
	X.ShowMassAndPower(); //����� enkBasis
	X.ShowMassAndStokes();  //����� petBasis

	X.print();
	cout << "\n";
	system("pause");
	return 0;
}


enkBasis::enkBasis()
{
	type = other;
	mass = 0;
	power = 0;
	SecretIndex = 88;
}

enkBasis::enkBasis(typeEnk t, float m, int p)
{
	type = t;
	mass = m;
	power = p;
	SecretIndex = (int)t * m;
}

void enkBasis::ShowMassAndPower()
{
	cout << endl << "Mass: " << mass << " - Power: " << power << endl;
}

 void enkBasis::print() 
{
	 cout << "\n��� �����������: " << GetTypeEnk(type);
	 cout << "\n�����: " << mass
		 << "\n��������: " << power << endl;
}

template <class T>
enk<T>::enk():enkBasis()
{
	name = NULL;
	cost = 0;
}

template <class T >
enk<T>::enk(typeEnk t, char* n, T c, double m, int p):enkBasis(t,m,p)
{
	name = new char[strlen(n) + 1];
	strcpy(name, n);
	cost = c;
}

template <class T>
enk<T>::enk(const enk &x)
{
	if (&x != this)
	{
		type = x.type;
		if (x.name != NULL)
		{
		name = new char[strlen(x.name) + 1];
		strcpy(name, x.name);
		}
		cost = x.cost;
		mass = x.mass;
		power = x.power;                           //������ �� ������� ����� � ����������� �
	}
}

template <class T>
enk<T>::~enk()
{
	//cout << "\n ~����� �����������\n";           //����� <--------------------------------
	if (name!=NULL)
	delete[] name;
}
template <class T>
void enk<T>::input(typeEnk t, char* n, T c, double m, int p)
{
	type = t;
	if (name != NULL)
		delete[] name;
	if (n != NULL)
	{
	name = new char[strlen(n) + 1];
	strcpy(name, n);
	}
	cost = c;
	mass = m;
	power = p;
}
template <class T>
void  enk<T>::print()

{
	cout << "\n���: " << GetTypeEnk(type) << " �������: "; if (name != NULL)cout << name; else cout << "��� ��������";
	cout << "\n���������: " << cost
		<< "\n�����: " << mass
		<< "\n��������: " << power << endl;
}
template <class T>
void  enk<T>::copy(const enk &x)
{
	if (&x != this)
		this->input(x.type, x.name, x.cost, x.mass, x.power);
}
template <class T>
enk<T> enk<T>::summa(enk b)
{
	enk h;
	h.type = other;
	h.name = new char[strlen(name) + strlen(b.name) + 2];
	strcpy(h.name, name);
	strcat(h.name, "+");
	strcat(h.name, b.name);

	h.cost = cost + b.cost;
	h.mass = mass + b.mass;
	h.power = power + b.power;
	return h;
}
template <class T>
bool  enk<T>::sravn(enk x)
{
	return (type == x.type && !strcmp(name, x.name) && cost == x.cost && mass == x.mass && power == x.power);

}
//template <class N>
// bool operator == (enk<N> c1, enk<N> x)
//{
//	return (c1.type == x.type && !strcmp(c1.name, x.name) && c1.cost == x.cost && c1.mass == x.mass && c1.power == x.power);
//}
// template <class N>
// bool operator != (enk<N> c1, enk<N> x)
// {
//	 return !(c1.type == x.type && !strcmp(c1.name, x.name) && c1.cost == x.cost && c1.mass == x.mass && c1.power == x.power);
// }

