// a1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/*
Name: Leonardo Vasilev,2000213591, Assignment #1
Description: a program for adding subtracting and multiplying matrices
Input: a file with valid matrices in it eg
3 3
1 2 3
0 1 2
5 4 3

3 3
1 22 3
0 1 2
5 3 2


Output the result of adding subtracting and multiplying the two matrices
*/


#include <iostream>
#include <cstdio>	

/*
Class identifier: a node class for a linked list
constructors: n/a, initialize variables manually
public members: nodes and data are public
static members: n/a 
*/
template<class T>
class node
{
public:
	node * left;
	node * right;
	node * up;
	node * down;

	T data;

	bool visited = false;
	node();
	~node();

private:

};
/*
Class identifier: a container class for a matrix
constructors: n/a, initialize variables manually
public members: a single node pointer pointing to a matrix in memory 
i,j the dimensions of the matrix
static members: n/a
*/
class Matrix
{
public:
	node<int> * matrixHead;
	int i, j;
	Matrix();
	~Matrix();

private:

};


/*
function_identifier: constructor
paramaters:
return value: 
*/
Matrix::Matrix()
{
	i = j = 0;
}

/*
function_identifier:destructor
paramaters:
return value:
*/
Matrix::~Matrix()
{
}

/*
function_identifier:constructor 
paramaters:
return value:
*/
template<class T>
node<T>::node()
{

}

/*
function_identifier:destructor 
paramaters:
return value:
*/
template<class T>
node<T>::~node<T>()
{
	//test
}

 
/*
function_identifier:function to create a linked list matrix from an array matrix 
paramaters:a double array of integers 
i, j as iterators 
sx , sy the dimensions of the matrix
Node * to point to the previous call so the matrix can be connected throughly 
return value:
*/
template<typename T>
node<T> * create(int ** arr,int i, int j, int sx, int sy, node<T> * prev) {


	if ((i>=sx || j >=sy))//check if size of matrix has been exceeds
	{
		return NULL;
	}

	node<T> * temp = new node<T>;
	temp->data = arr[i][j];
	//set the connections for all the sides
	temp->right = create<T>(arr, i, j + 1, sx, sy,temp);
	temp->left = prev;
	temp->up = prev;
	temp->down = create<T>(arr, i + 1, j, sx, sy,temp);
	return temp;

}

 
/*
FUnction to add matrices, matrices have to be of the same size.
Paramaters:
A - a linked list matrix to add 
B - same as A
Returns a matrix which is the  result of adding A +B 
*/
template<typename T>
node<T> * createAndAdd(node<T> * A, node<T> * B, node<T> * prev) {


	if (A == NULL || B == NULL)//since they are of equal size, we can check either for termination conditions
	{
		return NULL;
	}
	node<T> * temp = new node<T>;
	temp->data = A->data + B->data;
	//set the connections for all the sides
	temp->right = createAndAdd<T>(A->right, B->right, temp);
	temp->left = prev;
	temp->up = prev;
	temp->down = createAndAdd<T>(A->down, B->down, temp);
	return temp; //returns the head 

}

/*
function_identifier:function to print the contents of a linked list matrix, prints some junk too 
paramaters:a linked list matrix 
return value:optional returns some pointer
*/
template<typename T>
node<T> * printNode(node<T> * A,  node<T> * prev) {


	if (A == NULL  )//since they are of equal size, we can check either for termination conditions
	{
		return NULL;
	}

		node<T> * temp = new node<T>;
		temp->data = A->data;

		if (!A->visited)
		{
			std::cout << A->data << " "; //print the element 
			A->visited = true;
			
		}
		

									 //set the connections for all the sides
		temp->right = printNode<T>(A->right, temp);
		temp->left = prev;
		temp->up = prev;
		std::cout << std::endl;

		temp->down = printNode<T>(A->down, temp);


		return temp; //returns the head
 


}

/*
function_identifier:recursive matrix subtraction func
paramaters:two matrices and a pointer to the node in the last function
return value: a new linked list matrix which is the difference between the matrices subtracted 
*/
template<typename T>
node<T> * createAndSub(node<T> * A, node<T> * B, node<T> * prev) {


	if (A == NULL || B == NULL)//since they are of equal size, we can check either for termination conditions
	{
		return NULL;
	}
	node<T> * temp = new node<T>;
	temp->data = A->data - B->data;
	//set the connections for all the sides
	temp->right = createAndSub<T>(A->right, B->right, temp);
	temp->left = prev;
	temp->up = prev;
	temp->down = createAndSub<T>(A->down, B->down, temp);
	return temp; //returns the head 

}

/*
function_identifier:func to add two matrices
paramaters:matrix a and b 
return value:matrix c which is the summation of the two matrices
*/
Matrix *  matAdd(Matrix * matA, Matrix * matB) {
	if (matA->i!= matB->i || matA->j != matB->j)
	{
		return NULL;  //error have to have same size 
	}

	Matrix *m = new Matrix;
	m->i = matA->i;
	m->j = matB->j;
	m->matrixHead = createAndAdd<int>(matA->matrixHead, matB->matrixHead, NULL);
	if (m->matrixHead == NULL)
	{
		return NULL;
	}
	return m;
}



/*
function_identifier:function to subtract two matrices
paramaters: matrix a and b 
return value:matrix c which is the difference between the two matrices
*/
template<typename T>
Matrix *  matSub(Matrix * matA, Matrix * matB) {
	if (matA->i != matB->i || matA->j != matB->j)
	{
		return NULL;  //error have to have same size 
	}

	Matrix *m = new Matrix;
	m->i = matA->i;
	m->j = matB->j;
	m->matrixHead = createAndSub<int>(matA->matrixHead, matB->matrixHead, NULL);
	if (m->matrixHead == NULL)
	{
		return NULL;
	}
	return m;
}


/*
function_identifier:function to multiply two matrices
paramaters: matrix a and b to be multiplied 
return value: matrix c which is the product 
*/
template<typename T>
Matrix *  matMul(Matrix * matA, Matrix * matB) {
	if (matA->j!=matB->i)
	{
		return NULL;//error rows must equal columns 
	}
	Matrix *m = new Matrix;
	m->i = matA->i;
	m->j = matB->j;
	int **arr;
	//do the dot product 
	arr = new int*[m->j];
	for (int i = 0; i < m->j; i++)
	{
		arr[i] = new int[m->i];
	}


	typedef node<T> * node;
	node  Aptr, Bptr, aptr, bptr, headptr;

	//loop iteration pointers 
	Aptr = matA->matrixHead;
	Bptr = matB->matrixHead;
	aptr = Aptr;
	bptr = Bptr;
	headptr = Aptr; 


	int i, j;
	i = j = 0;
	
	//init with zeroes 
	for (int a = 0; a < m->i; a++)
	{
		for (int b = 0; b < m->j; b++)
		{
			arr[a][b] = 0;
		}
	}


	while (Aptr != NULL)
	{
		while (Bptr!=NULL)
		{
			while (bptr != NULL)
			{
				arr[i][j] += aptr->data * bptr->data;
				bptr = bptr->down; //move to the 
				aptr = aptr->right; //next element in each row, column 
			}
			Bptr = Bptr->right; //move to the next column in the second matrix 
			bptr = Bptr;
			aptr = Aptr;		//reset to first element in the row 
			j++;				//change col in new matrix 
		}
		i++;					//change row in new matrix 
		Aptr = Aptr->down;		//move to the next row in the first matrix 
		Bptr = matB->matrixHead;	//reset to the index pointer 
		aptr = Aptr;
		bptr = Bptr;
		j = 0;
	}
	

	m->matrixHead = create<T>(arr, 0, 0, m->i, m->j, NULL);

	node * result;

	return m;
}


/*
function_identifier:main entry point for the program
paramaters:void 
return value: 0 if successful 
*/

class point
{
public:
	point();
	~point();
	int x, y; 

private:

};

point::point()
{
	x = y = 0;
}

point::~point()
{
}

#include <vector>

int main()
{
	int cases = 0;
	std::scanf("%d", &cases); 
	int n = 0; 
	int xstart = 0;
	int ystart = 0; 
	int xend = 0;
	int yend = 0; 
	int W = 0; 
	
	std::vector<point> points;

	for (int casee = 0; casee < cases; casee++)
	{
		std::scanf("%d", &n);
		scanf("%d", &xstart);
		scanf("%d", &ystart);
		scanf("%d", &xend);
		scanf("%d", &yend);

		scanf("%d", &W);
		for (size_t i = 0; i < W; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{

			}
		}

	}
	typedef Matrix * Mat;

	/*Create first matrix
	*/
	int x, y;
	x = y = 0;


	scanf("%d", &x); //the number of rows 
	scanf("%d", &y); // the # of numbers in each row 

	int ** arr = new int*[y];  //(int**)malloc(sizeof(int*) * x);
	for (int i = 0; i < y; i++)
	{
		arr[i] = new int[x];
	}

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			scanf("%d", &arr[i][j]);
		}
	}

	node<int> * head = create<int>(arr, 0, 0, x, y,NULL);

	Mat A= new Matrix;
	A->matrixHead = head;
	A->i = x;
	A->j = y;
	/*
	Create second matrix
	
	*/
	int x2, y2;
	x2 = y2 = 0;

	scanf("%d", &x2); //the number of rows 
	scanf("%d", &y2); // the # of numbers in each row 

	int ** arr2 = new int*[y2];  //(int**)malloc(sizeof(int*) * x);
	for (int i = 0; i < y2; i++)
	{
		arr2[i] = new int[x2];
	}

	for (int i = 0; i < x2; i++)
	{
		for (int j = 0; j < y2; j++)
		{
			scanf("%d", &arr2[i][j]);
		}
	}


	node<int> * head2 = create<int>(arr2, 0, 0, x2, y2, NULL);
	Mat B = new Matrix;
	B->matrixHead = head2;
	B->i = x2;
	B->j = y2;

	/*start arithmetic 
	
	*/
	Mat AplusB = matAdd(A, B);
	if (AplusB == NULL)
	{
		std::cout << "error with matrix size in addition" << std::endl;
	}
	std::cout << "matrix addition: " << std::endl;
	node<int> * varr = printNode<int>(AplusB->matrixHead, NULL);


	Mat amulB = matMul<int>(A, B);
	if (amulB == NULL)
	{
		std::cout << "error with matrix size in multiplication" << std::endl;
	}
	std::cout << "matrix multiplication: " << std::endl;
	printNode<int>(amulB->matrixHead, NULL);


	Mat AsubB = matSub<int>(A, B);
	if (AsubB == NULL)
	{
		std::cout << "error with matrix size in subtraction" << std::endl;
	}
	std::cout << "matrix subtraction: " << std::endl;
	printNode<int>(AsubB->matrixHead, NULL);

	int s = 0;

    return 0;
}

