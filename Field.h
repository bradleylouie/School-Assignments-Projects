#include <vector>
#include <stdexcept>
using namespace std;
class Field
{
    public:
        Field( const vector<vector<int>> & input )
        {
            matrix = input;
            row_size = matrix.size();
            col_size = matrix.at(0).size();
            initWeightMatrix();
        }

        Field( vector<vector<int>> && input )
        {
            matrix = move(input);
            row_size = matrix.size();
            col_size = matrix.at(0).size();
            initWeightMatrix();
        }

        int Weight( int x1, int y1, int x2, int y2 )
        {
            if (x1 < 0 or y1 < 0 or x2 < 0 or y2 < 0 or x1 >= col_size or y1 >= row_size or x2 >= col_size or y2 >= row_size) 
                throw out_of_range ("Weight() given parameters out of range");

            int top, left, bottom, right;
            if (x1 < x2) { left = x1; right = x2; }
            else         { left = x2; right = x1; }
            if (y1 < y2) { top = y1; bottom = y2; }
            else         { top = y2; bottom = y1; }

            int wt = weight_matrix[bottom][right];
            if (top != 0)
                wt -= weight_matrix[top-1][right];
            if (left != 0)
                wt -= weight_matrix[bottom][left-1];
            if (top != 0 and left != 0)
                wt += weight_matrix[top-1][left-1];
            return wt;
        }

        int PathCost()
        {
            vector<vector<int>> path_cost_matrix(row_size, vector<int>(col_size, 0));
            path_cost_matrix[0][0] = matrix[0][0];

            for (int row{1}; row < row_size; ++row)
                path_cost_matrix[row][0] = weight_matrix[row][0];
            for (int col{1}; col < col_size; ++col)
                path_cost_matrix[0][col] = weight_matrix[0][col];
            
            for (int row{1}; row < row_size; ++row)
                for (int col{1}; col < col_size; ++col)
                    if (path_cost_matrix[row-1][col] <= path_cost_matrix[row][col-1])
                        path_cost_matrix[row][col] = path_cost_matrix[row-1][col] + matrix[row][col];
                    else
                        path_cost_matrix[row][col] = path_cost_matrix[row][col-1] + matrix[row][col];
            
            return path_cost_matrix[row_size-1][col_size-1];
        }
    private:
        vector<vector<int>> matrix, weight_matrix;
        int row_size, col_size;

        void initWeightMatrix()
        {
            weight_matrix = vector<vector<int>>(row_size, vector<int>(col_size, 0));
            weight_matrix[0][0] = matrix[0][0];

            for (int row{1}; row < row_size; ++row)
                weight_matrix[row][0] = weight_matrix[row-1][0] + matrix[row][0];
            for (int col{1}; col < col_size; ++col)
                weight_matrix[0][col] = weight_matrix[0][col-1] + matrix[0][col];
            
            for (int row{1}; row < row_size; ++row)
                for (int col{1}; col < col_size; ++col)
                    weight_matrix[row][col] = weight_matrix[row-1][col] + weight_matrix[row][col-1] - weight_matrix[row-1][col-1] + matrix[row][col];
        }
};

/*#include <iostream>

int main(){
    vector<vector<int>> matrix;
    for (int i{0}; i < 6; i++){
        matrix.push_back(vector<int>());
        for (int k{0}; k < 6; k++){
            int r = rand() % 10;
            matrix[i].push_back(r);
            cout << r << " ";
        }
        cout << endl;
    }
    Field f(matrix);
    cout << f.Weight(1,1,4,4) << endl;
    cout << f.PathCost();
}*/