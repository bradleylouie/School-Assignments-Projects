#ifndef SQUARE_MATRIX
#define SQUARE_MATRIX

template<typename Type>
class SquareMatrix
{
    public:
        ~SquareMatrix()
        {
            delete[] ptr;
            ptr = nullptr;
        }

        SquareMatrix() //default constructor
        { 
            ptr = nullptr; 
        } 

        SquareMatrix (const SquareMatrix & rhs ) //copy constructor
        {
            if (rhs.ptr)
            {
                size_i = rhs.size_i;
                ptr = new Type[size_i*size_i];
                for (int i = 0; i < size_i*size_i; i++)
                    ptr[i] = rhs.ptr[i];
            }
            else
                ptr = nullptr;
        }

        SquareMatrix & operator= ( const SquareMatrix & rhs ) //copy assignment
        {
            //errors will occur if a self-assignment is performed (this == &rhs)
            
            if (ptr)
            {
                if (rhs.ptr)
                {
                    resize(rhs.size_i);
                }
                else
                {
                    delete[] ptr;
                    ptr = nullptr;
                }
            }
            else
            {
                if (rhs.ptr)
                {
                    size_i = rhs.size_i;
                    ptr = new Type[size_i*size_i];
                }
                else
                {
                    ptr = nullptr;
                }
            }
            
            for (int i = 0; i < size_i*size_i; i++)
                ptr[i] = rhs.ptr[i];

            return *this;
        }
        
        SquareMatrix( SquareMatrix && rhs ) //move constructor
        { 
            if (rhs.ptr)
            {
                ptr = rhs.ptr;
                rhs.ptr = nullptr;
            }
        }
        SquareMatrix & operator= ( SquareMatrix && rhs ) //move assignment
        {
            if (rhs.ptr)
            {
                ptr = rhs.ptr;
                rhs.ptr = nullptr;
            }
            else
            {
                ptr = nullptr;
            }
            return *this;
        }

        bool operator== ( const SquareMatrix & comparison ) const
        {
            if (size_i == comparison.size_i )
            {
                for (int i = 0; i < size_i*size_i; i++){
                    std::cout<<i;
                    if (ptr[i] != comparison.ptr[i])
                        return false;
                }
                return true;
            }
            else
                return false;
        }

        //assume rhs is the same size
        SquareMatrix operator+ ( const SquareMatrix & rhs ) const
        {
            SquareMatrix<Type> new_matrix = SquareMatrix<Type>();
            new_matrix.resize(size_i);
            for (int i = 0; i < size_i*size_i; i++)
                new_matrix.ptr[i] = ptr[i] + rhs.ptr[i];
            return new_matrix;
        }

        void resize(int new_size)
        {
            delete[] ptr;
            size_i = new_size;
            ptr = new Type[size_i*size_i];
        }

        Type& at(int col, int row)
        {
            return ptr[(row*size_i) + col];
        }

        int size() const
        {
            return size_i;
        }

    private:
        Type* ptr;
        int size_i;
        
};

#endif