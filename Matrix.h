/*
 *  Name:   Burak
 *  SurName:Şen
 *  Id:     150170063
 */


#ifndef MATRIX_H
#define MATRIX_H

template<class MatrixTemplate>
class Matrix{
    MatrixTemplate **data;
    int row,col;
    int selRow,selCol; // these variables for seeing which data is chosen
    public:
        Matrix(int rows, int cols){ // template class constructor

            setCol(cols); // setting row and column
            setRow(rows);

            data = new MatrixTemplate*[row]; // allocate the data rows

            for(int i = 0; i < row; i++){ // and allocate the data columns for each rows
                data[i] = new MatrixTemplate[col];
            }
        }

        void setRow(int row){ this->row = row; } // setting row
        void setCol(int col){ this->col = col; } // setting column
        MatrixTemplate& operator()(int, int); // operator () overload

        void operator<=(double); //operator overload <=
        MatrixTemplate& operator+=(double); // operator overload +=
        ~Matrix();
};

template<class MatrixTemplate>
MatrixTemplate& Matrix<MatrixTemplate>::operator()(int row, int col) // in this overload function we set which data chosen
{                                                                    // and return this data
    this->selCol = col;//set column of the chosen data
    this->selRow = row;//set row of the chosen data
    return data[row][col]; //return chosen data
}

template<class MatrixTemplate>
void Matrix<MatrixTemplate>::operator <= (double input) { //in this overload function we fill all the data cells with given value
    for(int i = 0; i < this->row; i++){
        for(int j = 0; j < this->col; j++){
            this->data[i][j] = input;
        }
    }
}

template<class MatrixTemplate>
MatrixTemplate& Matrix<MatrixTemplate>::operator += (double input) {//in this overload function we sum the chosen data with given value
    return this->data[this->selRow][this->selCol] += input; //chosen row and chosen col
}

template<class MatrixTemplate>
Matrix<MatrixTemplate>::~Matrix(){ // destructor of the matrix
    for(int i = 0; i < row; i++){ // for all rows we delete data columns inside of the rows
        delete [] data[i];
    }
    delete [] data; // and we delete the rows
}


#endif //MATRIX_H
